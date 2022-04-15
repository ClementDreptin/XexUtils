// Original version made my iMoD1998 (https://gist.github.com/iMoD1998/4aa48d5c990535767a3fc3251efc0348)

#pragma once


#define MASK_N_BITS(N) ((1 << (N)) - 1)

#define POWERPC_HI(X) ((X >> 16) & 0xFFFF)
#define POWERPC_LO(X) (X & 0xFFFF)

// PowerPC most significant bit is addressed as bit 0 in documentation.
#define POWERPC_BIT32(N) (31 - N)

// Opcode is bits 0-5. 
// Allowing for op codes ranging from 0-63.
#define POWERPC_OPCODE(OP)       (OP << 26)
#define POWERPC_OPCODE_ADDI      POWERPC_OPCODE(14)
#define POWERPC_OPCODE_ADDIS     POWERPC_OPCODE(15)
#define POWERPC_OPCODE_BC        POWERPC_OPCODE(16)
#define POWERPC_OPCODE_B         POWERPC_OPCODE(18)
#define POWERPC_OPCODE_BCCTR     POWERPC_OPCODE(19)
#define POWERPC_OPCODE_ORI       POWERPC_OPCODE(24)
#define POWERPC_OPCODE_EXTENDED  POWERPC_OPCODE(31) // Use extended opcodes.
#define POWERPC_OPCODE_STW       POWERPC_OPCODE(36)
#define POWERPC_OPCODE_LWZ       POWERPC_OPCODE(32)
#define POWERPC_OPCODE_LD        POWERPC_OPCODE(58)
#define POWERPC_OPCODE_STD       POWERPC_OPCODE(62)
#define POWERPC_OPCODE_MASK      POWERPC_OPCODE(63)

#define POWERPC_EXOPCODE(OP)     (OP << 1)
#define POWERPC_EXOPCODE_BCCTR   POWERPC_EXOPCODE(528)
#define POWERPC_EXOPCODE_MTSPR   POWERPC_EXOPCODE(467)

// SPR field is encoded as two 5 bit bitfields.
#define POWERPC_SPR(SPR) static_cast<DWORD>(((SPR & 0x1F) << 5) | ((SPR >> 5) & 0x1F))

// Instruction helpers.
//
// rD - Destination register.
// rS - Source register.
// rA/rB - Register inputs.
// SPR - Special purpose register.
// UIMM/SIMM - Unsigned/signed immediate.
#define POWERPC_ADDI(rD, rA, SIMM)  static_cast<DWORD>(POWERPC_OPCODE_ADDI | (rD << POWERPC_BIT32(10)) | (rA << POWERPC_BIT32(15)) | SIMM)
#define POWERPC_ADDIS(rD, rA, SIMM) static_cast<DWORD>(POWERPC_OPCODE_ADDIS | (rD << POWERPC_BIT32(10)) | (rA << POWERPC_BIT32(15)) | SIMM)
#define POWERPC_LIS(rD, SIMM)       POWERPC_ADDIS(rD, 0, SIMM) // Mnemonic for addis %rD, 0, SIMM
#define POWERPC_LI(rD, SIMM)        POWERPC_ADDIrD, 0, SIMM)   // Mnemonic for addi %rD, 0, SIMM
#define POWERPC_MTSPR(SPR, rS)      static_cast<DWORD>(POWERPC_OPCODE_EXTENDED | (rS << POWERPC_BIT32(10)) | (POWERPC_SPR(SPR) << POWERPC_BIT32(20)) | POWERPC_EXOPCODE_MTSPR)
#define POWERPC_MTCTR(rS)           POWERPC_MTSPR(9, rS) // Mnemonic for mtspr 9, rS
#define POWERPC_ORI(rS, rA, UIMM)   static_cast<DWORD>(POWERPC_OPCODE_ORI | (rS << POWERPC_BIT32(10)) |  (rA << POWERPC_BIT32(15)) | UIMM)
#define POWERPC_BCCTR(BO, BI, LK)   static_cast<DWORD>(POWERPC_OPCODE_BCCTR | (BO << POWERPC_BIT32(10)) | (BI << POWERPC_BIT32(15) | LK & 1) | POWERPC_EXOPCODE_BCCTR)
#define POWERPC_STD(rS, DS, rA)     static_cast<DWORD>(POWERPC_OPCODE_STD | (rS << POWERPC_BIT32(10)) | (rA << POWERPC_BIT32(15)) | (static_cast<WORD>(DS) & 0xFFFF))
#define POWERPC_LD(rS, DS, rA)      static_cast<DWORD>(POWERPC_OPCODE_LD | (rS << POWERPC_BIT32(10)) | (rA << POWERPC_BIT32(15)) | (static_cast<DWORD>(DS) & 0xFFFF))

// Branch related fields.
#define POWERPC_BRANCH_LINKED    1
#define POWERPC_BRANCH_ABSOLUTE  2
#define POWERPC_BRANCH_TYPE_MASK (POWERPC_BRANCH_LINKED | POWERPC_BRANCH_ABSOLUTE)

#define POWERPC_BRANCH_OPTIONS_ALWAYS (20)


namespace XexUtils
{

class Detour
{
public:
    /**
     * Constructor
     * 
     * @param pHookSource - The function that will be hooked.
     * @param pHookTarget - The function that the hook will be redirected to.
     */
    Detour(DWORD dwHookSourceAddress, const void *pHookTarget);

    /**
     * Destructor
     */
    ~Detour();

    /**
     * Sets up the detour.
     * @return true if the detour was set up successfully, false otherwise.
     */
    bool Install();

    /**
     * Removes the detour.
     * @return true if the detour was removed successfully, false otherwise.
     */
    bool Remove();

    /**
     * Get a pointer to the original function.
     * @return A pointer to the original function.
     */
    template<typename T>
    T GetOriginal() const
    {
        return reinterpret_cast<T>(m_pbTrampolineAddress);
    }

private:
    // The funtion we are pointing the hook to.
    const void *m_pHookTarget;

    // The function we are hooking.
    DWORD m_dwHookSourceAddress;

    // Pointer to the trampoline for this detour.
    byte *m_pbTrampolineAddress;        

    // Any bytes overwritten by the hook.
    byte m_pOriginalInstructions[30];  

    // The amount of bytes overwritten by the hook.
    size_t m_uiOriginalLength;          

    // Shared
    static byte s_pTrampolineBuffer[200 * 20];
    static size_t s_uiTrampolineSize;

    /**
     * Writes an unconditional branch to the destination address that will branch to the target address.
     *
     * @param Destination - Where the branch will be written to.
     * @param BranchTarget - The address the branch will jump to.
     * @param Linked - Branch is a call or a jump? aka bl or b
     * @param PreserveRegister - Preserve the register clobbered after loading the branch address.
     * @return The size of the branch in bytes.
     */
    static size_t WriteFarBranch(void *pDestination, const void *pBranchTarget, bool bLinked = true, bool bPreserveRegister = false);

    /**
     * Writes both conditional and unconditional branches using the count register to the destination address that will branch to the target address.
     *
     * @param Destination - Where the branch will be written to.
     * @param BranchTarget - The address the branch will jump to.
     * @param Linked - Branch is a call or a jump? aka bl or b
     * @param PreserveRegister - Preserve the register clobbered after loading the branch address.
     * @param BranchOptions - Options for determining when a branch to be followed.
     * @param ConditionRegisterBit - The bit of the condition register to compare.
     * @param RegisterIndex - Register to use when loading the destination address into the count register.
     * @return The size of the branch in bytes.
     */
    static size_t WriteFarBranchEx(void *pDestination, const void *pBranchTarget, bool bLinked = false, bool bPreserveRegister = false, DWORD dwBranchOptions = POWERPC_BRANCH_OPTIONS_ALWAYS, byte bConditionRegisterBit = 0, byte bRegisterIndex = 0);

    /**
     * Copies and fixes relative branch instructions to a new location.
     *
     * @param Destination - Where to write the new branch.
     * @param Source - Address to the instruction that is being relocated.
     * @return The size of the branch in bytes.
     */
    static size_t RelocateBranch(DWORD *pdwDestination, const DWORD *pdwSource);

    /**
     * Copies an instruction enusuring things such as PC relative offsets are fixed.
     *
     * @param Destination - Where to write the new instruction(s).
     * @param Source - Address to the instruction that is being copied.
     * @return The size of the instruction in bytes.
     */
    static size_t CopyInstruction(DWORD *pdwDestination, const DWORD *pdwSource);
};

}
