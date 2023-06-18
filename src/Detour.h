// Original version made my iMoD1998 (https://gist.github.com/iMoD1998/4aa48d5c990535767a3fc3251efc0348)

#pragma once

#define POWERPC_BRANCH_OPTIONS_ALWAYS 20
#define TRAMPOLINE_BUFFER_MAX_SIZE 0x1000

namespace XexUtils
{

typedef uint32_t POWERPC_INSTRUCTION;

class Detour
{
public:
    Detour(uintptr_t hookSourceAddress, const void *pHookTarget);
    Detour(void *pHookSource, const void *pHookTarget);

    ~Detour();

    bool Install();

    bool Remove();

    template<typename T>
    inline T GetOriginal() const
    {
        return reinterpret_cast<T>(m_pTrampolineDestination);
    }

private:
    const void *m_pHookTarget;

    void *m_pHookSource;

    void *m_pTrampolineDestination;

    uint8_t m_OriginalInstructions[30];

    size_t m_OriginalLength;

    static uint8_t s_TrampolineBuffer[TRAMPOLINE_BUFFER_MAX_SIZE];

    static size_t s_TrampolineSize;

    // Function that contains to constructor logic, it's meant to share the same logic for multiple constructors.
    // This is necessary because C++0x doesn't support calling one constructor from another constructor.
    void Init(void *pHookSource, const void *pHookTarget);

    // Write both conditional and unconditional branches using the count register to the destination address that will branch to the target address.
    size_t WriteFarBranch(void *pDestination, const void *pBranchTarget, bool linked = false, bool preserveRegister = false, uint32_t branchOptions = POWERPC_BRANCH_OPTIONS_ALWAYS, uint8_t conditionRegisterBit = 0, uint8_t registerIndex = 0);

    // Copy and fix relative branch instructions to a new location.
    size_t RelocateBranch(void *pDestination, const void *pSource);

    // Copy an instruction enusuring things such as PC relative offsets are fixed.
    size_t CopyInstruction(void *pDestination, const void *pSource);
};

}
