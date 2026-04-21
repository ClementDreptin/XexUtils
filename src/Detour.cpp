// Very inspired by the "Xbox 360 Detours" gist from iMoD1998
// https://gist.github.com/iMoD1998/4aa48d5c990535767a3fc3251efc0348

#include "pch.h"
#include "Detour.h"

#include "General.h"
#include "Kernel.h"
#include "Memory.h"

namespace XexUtils
{

#define MASK_N_BITS(N) ((1 << (N)) - 1)

#define HI(X) (((X) >> 16) & MASK_N_BITS(16))
#define LO(X) ((X) & MASK_N_BITS(16))

#define OPCODE_B 0x48000000
#define OPCODE_BC 0x40000000
#define OPCODE_MASK 0xFC000000

#define BRANCH_LINKED 1
#define BRANCH_ABSOLUTE 2

#define BRANCH_OPTIONS_ALWAYS 20

#define LIS(rD, SIMM) (0x3C000000 | ((rD) << 21) | (SIMM))
#define MTCTR(rS) (0x7C0903A6 | ((rS) << 21))
#define ORI(rS, rA, UIMM) (0x60000000 | ((rS) << 21) | ((rA) << 16) | (UIMM))
#define BCCTR(BO, BI, LK) (0x4C000420 | ((BO) << 21) | ((BI) << 16) | ((LK) & BRANCH_LINKED))
#define STD(rS, DS, rA) (0xF8000000 | ((rS) << 21) | ((rA) << 16) | ((int16_t)(DS) & MASK_N_BITS(16)))
#define LD(rS, DS, rA) (0xE8000000 | ((rS) << 21) | ((rA) << 16) | ((int16_t)(DS) & MASK_N_BITS(16)))

#pragma section(".text")

// This will hold all the instructions for all stubs. Allocating in an executable section
// isn't mandatory on real hardware because modded consoles have page permissions disabled,
// but this is necessary on Xenia, which emulates retail hardware
__declspec(allocate(".text")) Detour::POWERPC_INSTRUCTION Detour::s_Stubs[MAX_DETOUR_COUNT][MAX_INSTRUCTIONS_IN_STUB];
bool Detour::s_UsedSlots[MAX_DETOUR_COUNT] = {};
CRITICAL_SECTION Detour::s_CriticalSection = {};

Detour::Detour()
    : m_pSource(nullptr), m_pDestination(nullptr), m_SlotIndex(static_cast<size_t>(-1))
{
}

Detour::Detour(void *pSource, const void *pDestination)
    : m_pSource(pSource), m_pDestination(pDestination), m_SlotIndex(static_cast<size_t>(-1))
{
}

Detour::Detour(uintptr_t sourceAddress, const void *pDestination)
    : m_pSource(reinterpret_cast<void *>(sourceAddress)), m_pDestination(pDestination), m_SlotIndex(static_cast<size_t>(-1))
{
}

Detour::Detour(const std::string &moduleName, uint32_t ordinal, const void *pDestination)
    : m_pSource(ResolveExport(moduleName, ordinal)), m_pDestination(pDestination), m_SlotIndex(static_cast<size_t>(-1))
{
}

Detour::Detour(const std::string &moduleName, const std::string &importedModuleName, uint32_t ordinal, const void *pDestination)
    : m_pSource(GetModuleImport(moduleName, importedModuleName, ordinal)), m_pDestination(pDestination), m_SlotIndex(static_cast<size_t>(-1))
{
}

Detour::~Detour()
{
    Remove();
}

HRESULT Detour::Install()
{
    // Check for incorrect initialization
    if (m_pSource == nullptr || m_pDestination == nullptr)
    {
        DebugPrint("[XexUtils][Detour]: Error: source and/or destination addresses are null.");
        return E_FAIL;
    }

    // Prevent double detours
    if (m_SlotIndex != -1)
    {
        DebugPrint("[XexUtils][Detour]: Error: This detour has already been installed.");
        return E_FAIL;
    }

    // Initialize the synchronization object for the first instance
    if (s_CriticalSection.Synchronization.RawEvent[0] == 0)
        InitializeCriticalSection(&s_CriticalSection);

    // Grab the lock
    EnterCriticalSection(&s_CriticalSection);

    // Look for a free slot
    for (size_t i = 0; i < MAX_DETOUR_COUNT; i++)
    {
        if (!s_UsedSlots[i])
        {
            m_SlotIndex = i;
            break;
        }
    }

    if (m_SlotIndex == -1)
    {
        DebugPrint("[XexUtils][Detour]: Error: Max detour count reached (%i).", MAX_DETOUR_COUNT);
        LeaveCriticalSection(&s_CriticalSection);
        return E_FAIL;
    }

    // Apply the detour
    DetourFunctionStart();

    // Release the lock
    LeaveCriticalSection(&s_CriticalSection);

    return S_OK;
}

void Detour::Remove()
{
    // Restore the original instructions if needed
    if (m_SlotIndex != -1 && m_pSource != nullptr && MmIsAddressValid(m_pSource))
    {
        Memory::Write(m_pSource, m_Original);

        EnterCriticalSection(&s_CriticalSection);
        s_UsedSlots[m_SlotIndex] = false;
        LeaveCriticalSection(&s_CriticalSection);
    }

    m_pSource = nullptr;
    m_pDestination = nullptr;
    m_SlotIndex = static_cast<size_t>(-1);
    m_Original = Original();
}

Detour::Jump::Jump(const void *pTarget, bool linked, bool preserveR0, uint32_t branchOptions, uint8_t conditionRegisterBit)
{
    XASSERT(pTarget != nullptr);

    const uint8_t r0 = 0;
    const uint8_t r1 = 1;
    const uintptr_t targetAddress = reinterpret_cast<uintptr_t>(pTarget);
    size_t i = 0;

    // Store the previous value of r0 on the stack if requested
    if (preserveR0)
        Instructions[i++] = STD(r0, -0x30, r1);

    // Store the target address in r0 and move it to the count register
    Instructions[i++] = LIS(r0, HI(targetAddress));
    Instructions[i++] = ORI(r0, r0, LO(targetAddress));
    Instructions[i++] = MTCTR(r0);

    // Load the previous value of r0 from the stack back into r0 if requested
    if (preserveR0)
        Instructions[i++] = LD(r0, -0x30, r1);

    // Branch to the target address stored in the count register
    Instructions[i++] = BCCTR(branchOptions, conditionRegisterBit, linked); // bctr/bcctr/bctrl/bcctrl

    Size = i;
}

void Detour::Jump::Write(void *pDestination)
{
    XASSERT(pDestination != nullptr);

    memcpy(pDestination, Instructions, Size * sizeof(Instructions[0]));
}

void Detour::DetourFunctionStart()
{
    XASSERT(m_pSource != nullptr);
    XASSERT(m_pDestination != nullptr);
    XASSERT(m_SlotIndex != -1);

    // Copy the original instructions of the source function before detouring
    // to be able to restore them later
    m_Original = Memory::Read<Original>(m_pSource);
    size_t originalInstructionsCount = ARRAYSIZE(m_Original.Instructions);

    // Create the stub from the first 4 instructions of the source function.
    // This stub can be used by the destination function if it wants to
    // execute the original code of the source function
    POWERPC_INSTRUCTION *pSource = static_cast<POWERPC_INSTRUCTION *>(m_pSource);
    POWERPC_INSTRUCTION *pCurrentInstructionInStub = &s_Stubs[m_SlotIndex][0];
    for (size_t i = 0; i < originalInstructionsCount; i++)
    {
        POWERPC_INSTRUCTION opcode = pSource[i] & OPCODE_MASK;
        bool isBranch = opcode == OPCODE_B || opcode == OPCODE_BC;
        bool isAbsolute = (pSource[i] & BRANCH_ABSOLUTE) != 0;

        // If we encounter a relative branch, we need to relocate it because the
        // target, which is an offset, would be wrong after copying the instruction
        // to a different location. Absolute branches don't need to be relocated
        // and should not exist on Xbox 360
        if (isBranch && !isAbsolute)
        {
            Jump jump = RelocateBranch(&pSource[i]);
            jump.Write(pCurrentInstructionInStub);
            pCurrentInstructionInStub += jump.Size;
            continue;
        }

        // If we encounter any other type of instruction, we can copy it as is to
        // the stub
        Memory::Write(pCurrentInstructionInStub, pSource[i]);
        pCurrentInstructionInStub++;
    }

    // Make the stub jump back to the source function after the jump we inserted
    POWERPC_INSTRUCTION *pInstructionAfterBranch = &pSource[originalInstructionsCount];
    Jump jumpFromStubBackToSource(pInstructionAfterBranch, false, true);
    jumpFromStubBackToSource.Write(pCurrentInstructionInStub);

    // Finally, make the source function jump to the destination function
    Jump jumpFromSourceToDestination(m_pDestination);
    jumpFromSourceToDestination.Write(m_pSource);

    // Mark the current stub as used
    s_UsedSlots[m_SlotIndex] = true;
}

Detour::Jump Detour::RelocateBranch(const void *pLocation)
{
    XASSERT(pLocation != nullptr);

    uint32_t offsetSize = 0;
    uint32_t offsetBase = 2;
    uint32_t options = 0;
    uint8_t conditionRegisterBit = 0;

    // Get the instruction from its location
    POWERPC_INSTRUCTION instruction = Memory::Read<POWERPC_INSTRUCTION>(pLocation);

    // Get the opcode of the instruction. At this stage, we should never have anything
    // other than B or BC
    POWERPC_INSTRUCTION opcode = instruction & OPCODE_MASK;
    XASSERT(opcode == OPCODE_B || opcode == OPCODE_BC);

    // Note: bit indices in these comments use little-endian numbering (bit 0 = LSB = 2^0),
    // which is the opposite of the PowerPC documentation (where bit 0 = MSB)

    if (opcode == OPCODE_B)
    {
        // B instruction layout:
        // [31-26] opcode: 6 bits
        // [25-2 ] offset: 24 bits, signed, stored divided by 4
        // [1    ] absolute flag: 1 bit
        // [0    ] linked flag: 1 bit
        offsetSize = 24;
        options = BRANCH_OPTIONS_ALWAYS;
        conditionRegisterBit = 0;
    }
    else if (opcode == OPCODE_BC)
    {
        // BC instruction layout (32 bits):
        // [31-26] opcode: 6 bits
        // [25-21] options: 5 bits
        // [20-16] condition register bit: 5 bits
        // [15-2 ] offset: 14 bits, signed, stored divided by 4
        // [1    ] absolute flag: 1 bit
        // [0    ] linked flag: 1 bit
        offsetSize = 14;
        options = (instruction >> 21) & MASK_N_BITS(5);
        conditionRegisterBit = (instruction >> 16) & MASK_N_BITS(5);
    }

    // The branch instructions store the branch offset divided by 4 in the offset field.
    // To get the actual byte offset, we mask the offset field and shift it left by 2
    // (offsetBase), which is equivalent to the CPU concatenating 2 zero bits on the right
    // as described in the PowerPC documentation.
    // https://www.ibm.com/docs/en/aix/7.3.0?topic=set-b-branch-instruction
    intptr_t offset = instruction & (MASK_N_BITS(offsetSize) << offsetBase);

    // The offset variable only uses the first (offsetSize + offsetBase) bits and the
    // (offsetSize + offsetBase)th bit is the sign bit. Because the offset variable is 32-bit
    // and (offsetSize + offsetBase) is always lower than 32, if the sign bit is set, we
    // need to set all the bits from 32 to (offsetSize + offsetBase) to make it a valid
    // negative integer following two's complement
    if (offset & (1 << (offsetSize + offsetBase - 1)))
        offset |= ~MASK_N_BITS(offsetSize + offsetBase);

    void *pTarget = reinterpret_cast<void *>(reinterpret_cast<intptr_t>(pLocation) + offset);

    return Jump(pTarget, instruction & BRANCH_LINKED, true, options, conditionRegisterBit);
}

void *Detour::GetModuleImport(const std::string &baseModuleName, const std::string &importedModuleName, uint32_t ordinal)
{
    // Very inspired by this
    // https://github.com/TeaModz/XeLiveStealth-Full-Source/blob/master/XeLive/Hooking.cpp#L100

    // Usage example
    //
    // GetModuleImport("hud.xex", "xam.xex", 842);
    //
    // This would get a pointer to the 842nd function exported by xam.xex (XuiRegisterClass)
    // used by hud.xex

    // Get the module handle of the base module
    HMODULE moduleHandle = GetModuleHandle(baseModuleName.c_str());
    if (moduleHandle == nullptr)
    {
        DebugPrint(
            "[XexUtils][Detour]: Error: Could not get handle of module %s. Make sure it is loaded.",
            baseModuleName.c_str()
        );
        return nullptr;
    }

    // Get a pointer to the function we're looking for but from our module (so the one
    // this code is running in, not the base module)
    void *pFunc = ResolveExport(importedModuleName, ordinal);
    if (pFunc == nullptr)
    {
        DebugPrint(
            "[XexUtils][Detour]: Error: Could not resolve function number %d from module %s."
            "Make sure the module is loaded and exports at least %d functions.",
            ordinal,
            importedModuleName.c_str(),
            ordinal
        );
        return nullptr;
    }

    // Get the import descriptor of the base module
    LDR_DATA_TABLE_ENTRY *pDataTable = reinterpret_cast<LDR_DATA_TABLE_ENTRY *>(moduleHandle);
    XEX_IMPORT_DESCRIPTOR *pImportDesc = static_cast<XEX_IMPORT_DESCRIPTOR *>(
        RtlImageXexHeaderField(pDataTable->XexHeaderBase, XEX_HEADER_FIELD_IMPORT_DESCRIPTOR)
    );

    XASSERT(pImportDesc != nullptr);

    // Calculate the import table location from the import descriptor
    // The memory is laid out as such:
    //
    // ┌──────────────────────────────┐
    // │ XEX_IMPORT_DESCRIPTOR        │
    // │   uint32_t Size              │  => size: 0xC
    // │   uint32_t NameTableSize     │
    // │   uint32_t ModuleCount       │
    // ├──────────────────────────────┤
    // │ NAME_TABLE                   │  => size: NameTableSize
    // │ (unknown struct)             │
    // ├──────────────────────────────┤
    // │ XEX_IMPORT_TABLE 1           │
    // │ XEX_IMPORT_TABLE 2           │  => size: The sum of all XEX_IMPORT_TABLE TableSize fields
    // │ XEX_IMPORT_TABLE ...         │
    // │ XEX_IMPORT_TABLE ModuleCount │
    // └──────────────────────────────┘
    //
    // So the address of the first import table is
    // pImportDesc + sizeof(XEX_IMPORT_DESCRIPTOR) + pImportDesc->NameTableSize

    XEX_IMPORT_TABLE *pImportTable = reinterpret_cast<XEX_IMPORT_TABLE *>(
        reinterpret_cast<uintptr_t>(pImportDesc) + sizeof(XEX_IMPORT_DESCRIPTOR) + pImportDesc->NameTableSize
    );

    for (size_t i = 0; i < pImportDesc->ModuleCount; i++)
    {
        for (size_t j = 0; j < pImportTable->ImportCount; j++)
        {
            void *pImportStubAddress = Memory::Read<void *>(pImportTable->ImportStubAddr[j]);

            if (pImportStubAddress == pFunc)
                return reinterpret_cast<void *>(pImportTable->ImportStubAddr[j + 1]);
        }

        // Set pImportTable to the address of the next import table, which is the
        // address of the current import table + the size of the current import table
        pImportTable = reinterpret_cast<XEX_IMPORT_TABLE *>(
            reinterpret_cast<uintptr_t>(pImportTable) + pImportTable->TableSize
        );
    }

    DebugPrint(
        "[XexUtils][Detour]: Error: Could not find function number %d exported by %s used in %s.",
        ordinal,
        importedModuleName.c_str(),
        baseModuleName.c_str()
    );

    return nullptr;
}

}
