#include "pch.h"
#include "Detour.h"

#include "Xam_.h"


namespace XexUtils
{

byte Detour::s_pTrampolineBuffer[TRAMPOLINE_BUFFER_MAX_SIZE] = { 0 };
size_t Detour::s_uiTrampolineSize = 0;

Detour::Detour(DWORD dwHookSourceAddress, const void *pHookTarget)
{
    Init(reinterpret_cast<void *>(dwHookSourceAddress), pHookTarget);
}

Detour::Detour(void *pHookSource, const void *pHookTarget)
{
    Init(pHookSource, pHookTarget);
}

void Detour::Init(void *pHookSource, const void *pHookTarget)
{
    m_pHookSource = pHookSource;
    m_pHookTarget = pHookTarget;
    m_pTrampolineDestination = nullptr;
    m_uiOriginalLength = 0;

    Install();
}

Detour::~Detour()
{
    Remove();
}

bool Detour::Install()
{
    // Check if we are already hooked
    if (m_uiOriginalLength != 0)
        return false;

    const size_t HookSize = WriteFarBranch(nullptr, m_pHookTarget, false, false);

    // Save the original instructions for unhooking later on
    memcpy(m_pOriginalInstructions, m_pHookSource, HookSize);

    m_uiOriginalLength = HookSize;

    // Create trampoline and copy and fix instructions to the trampoline
    m_pTrampolineDestination = &s_pTrampolineBuffer[s_uiTrampolineSize];

    for (size_t i = 0; i < (HookSize / 4); i++)
    {
        const auto pdwInstruction = reinterpret_cast<DWORD *>(reinterpret_cast<DWORD>(m_pHookSource) + (i * 4));

        s_uiTrampolineSize += CopyInstruction(reinterpret_cast<DWORD *>(&s_pTrampolineBuffer[s_uiTrampolineSize]), pdwInstruction);
    }

    // Trampoline branches back to the original function after the branch we used to hook
    const void *pAfterBranchAddress = reinterpret_cast<void *>(reinterpret_cast<DWORD>(m_pHookSource) + HookSize);

    s_uiTrampolineSize += WriteFarBranch(&s_pTrampolineBuffer[s_uiTrampolineSize], pAfterBranchAddress, false, true);

    // Finally write the branch to the function that we are hooking
    WriteFarBranch(m_pHookSource, m_pHookTarget, false, false);

    return true;
}

bool Detour::Remove()
{
    if (m_pHookSource && m_uiOriginalLength)
    {
        // Trying to remove a hook from a game function after the game has been closed could cause a segfault so we
        // make sure the hook function is still loaded in memory
        bool bIsHookSourceAddressValid = Xam::IsAddressValid(m_pHookSource);
        if (bIsHookSourceAddressValid)
            memcpy(m_pHookSource, m_pOriginalInstructions, m_uiOriginalLength);

        m_uiOriginalLength = 0;
        m_pHookSource = nullptr;

        return true;
    }

    return false;
}

size_t Detour::WriteFarBranch(void *pDestination, const void *pBranchTarget, bool bLinked, bool bPreserveRegister)
{
    return WriteFarBranchEx(pDestination, pBranchTarget, bLinked, bPreserveRegister);
}

size_t Detour::WriteFarBranchEx(void *pDestination, const void *pBranchTarget, bool bLinked, bool bPreserveRegister, DWORD dwBranchOptions, byte bConditionRegisterBit, byte bRegisterIndex)
{
    const DWORD pBranchFarAsm[] =
    {
        POWERPC_LIS(bRegisterIndex, POWERPC_HI(reinterpret_cast<DWORD>(pBranchTarget))),                   // lis   %rX, BranchTarget@hi
        POWERPC_ORI(bRegisterIndex, bRegisterIndex, POWERPC_LO(reinterpret_cast<DWORD>(pBranchTarget))),   // ori   %rX, %rX, BranchTarget@lo
        POWERPC_MTCTR(bRegisterIndex),                                                                     // mtctr %rX
        POWERPC_BCCTR(dwBranchOptions, bConditionRegisterBit, bLinked)                                     // bcctr (bcctr 20, 0 == bctr)
    };

    const DWORD pBranchFarAsmPreserve[] =
    {
        POWERPC_STD(bRegisterIndex, -0x30, 1),                                                             // std   %rX, -0x30(%r1)
        POWERPC_LIS(bRegisterIndex, POWERPC_HI(reinterpret_cast<DWORD>(pBranchTarget))),                   // lis   %rX, BranchTarget@hi
        POWERPC_ORI(bRegisterIndex, bRegisterIndex, POWERPC_LO(reinterpret_cast<DWORD>(pBranchTarget))),   // ori   %rX, %rX, BranchTarget@lo
        POWERPC_MTCTR(bRegisterIndex),                                                                     // mtctr %rX
        POWERPC_LD(bRegisterIndex, -0x30, 1),                                                              // lwz   %rX, -0x30(%r1)
        POWERPC_BCCTR(dwBranchOptions, bConditionRegisterBit, bLinked)                                     // bcctr (bcctr 20, 0 == bctr)
    };

    const DWORD *pBranchAsm = bPreserveRegister ? pBranchFarAsmPreserve : pBranchFarAsm;
    const DWORD dwBranchAsmSize = bPreserveRegister ? sizeof(pBranchFarAsmPreserve) : sizeof(pBranchFarAsm);

    if (pDestination)
        memcpy(pDestination, pBranchAsm, dwBranchAsmSize);

    return dwBranchAsmSize;
}

size_t Detour::RelocateBranch(DWORD *pdwDestination, const DWORD *pdwSource)
{
    const DWORD dwInstruction = *pdwSource;
    const DWORD dwInstructionAddress = reinterpret_cast<DWORD>(pdwSource);

    // Absolute branches don't need to be handled
    if (dwInstruction & POWERPC_BRANCH_ABSOLUTE)
    {
        *pdwDestination = dwInstruction;

        return 4;
    }

    size_t uiBranchOffsetBitSize = 0;
    int iBranchOffsetBitBase = 0;
    DWORD dwBranchOptions = 0;
    byte bConditionRegisterBit = 0;

    switch (dwInstruction & POWERPC_OPCODE_MASK)
    {
        // B - Branch
        // [Opcode]            [Address]           [Absolute] [Linked]
        //   0-5                 6-29                  30        31
        //
        // Example
        //  010010   0000 0000 0000 0000 0000 0001      0         0
    case POWERPC_OPCODE_B:
        uiBranchOffsetBitSize = 24;
        iBranchOffsetBitBase = 2;
        dwBranchOptions = POWERPC_BRANCH_OPTIONS_ALWAYS;
        bConditionRegisterBit = 0;
        break;

        // BC - Branch Conditional
        // [Opcode]   [Branch Options]     [Condition Register]         [Address]      [Absolute] [Linked]
        //   0-5           6-10                    11-15                  16-29            30        31
        //
        // Example
        //  010000        00100                    00001             00 0000 0000 0001      0         0
    case POWERPC_OPCODE_BC:
        uiBranchOffsetBitSize = 14;
        iBranchOffsetBitBase = 2;
        dwBranchOptions = (dwInstruction >> POWERPC_BIT32(10)) & MASK_N_BITS(5);
        bConditionRegisterBit = (dwInstruction >> POWERPC_BIT32(15)) & MASK_N_BITS(5);
        break;
    }

    // Even though the address part of the instruction begins from bit 29 in the case of bc and b.
    // The value of the first bit is 4 as all addresses are aligned to for 4 for code therefore,
    // the branch offset can be caluclated by anding in place and removing any suffix bits such as the 
    // link register or absolute flags.
    DWORD dwBranchOffset = dwInstruction & (MASK_N_BITS(uiBranchOffsetBitSize) << iBranchOffsetBitBase);

    // Check if the MSB of the offset is set
    if (dwBranchOffset >> ((uiBranchOffsetBitSize + iBranchOffsetBitBase) - 1))
    {
        // Add the nessasary bits to our integer to make it negative
        dwBranchOffset |= ~MASK_N_BITS(uiBranchOffsetBitSize + iBranchOffsetBitBase);
    }

    const void *pBranchAddress = reinterpret_cast<void *>(dwInstructionAddress + dwBranchOffset);

    return WriteFarBranchEx(pdwDestination, pBranchAddress, dwInstruction & POWERPC_BRANCH_LINKED, true, dwBranchOptions, bConditionRegisterBit);
}

size_t Detour::CopyInstruction(DWORD *pdwDestination, const DWORD *pdwSource)
{
    const DWORD dwInstruction = *pdwSource;

    switch (dwInstruction & POWERPC_OPCODE_MASK)
    {
    case POWERPC_OPCODE_B:  // B BL BA BLA
    case POWERPC_OPCODE_BC: // BEQ BNE BLT BGE
        return RelocateBranch(pdwDestination, pdwSource);
    default:
        *pdwDestination = dwInstruction;
        return 4;
    }
}

}
