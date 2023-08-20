#pragma once

#define MAX_HOOK_COUNT 100
#define NUM_INSTRUCTIONS_IN_JUMP 4

namespace XexUtils
{

class Detour
{
public:
    Detour(void *pSource, const void *pDestination);

    Detour(uintptr_t sourceAddress, const void *pDestination);

    Detour(const std::string &moduleName, uint32_t ordinal, const void *pDestination);

    Detour(const std::string &moduleName, const std::string &importedModuleName, uint32_t ordinal, const void *pDestination);

    ~Detour();

    HRESULT Install();

    void Remove();

    template<typename T>
    inline T GetOriginal() const
    {
        return reinterpret_cast<T>(&s_StubSection[m_HookIndex]);
    }

private:
    typedef uint32_t POWERPC_INSTRUCTION;
    typedef uint8_t POWERPC_INSTRUCTION_TYPE;

    struct Stub
    {
        POWERPC_INSTRUCTION Instructions[20]; // DetourFunctionStart can copy up to 20 instructions

        Stub() { ZeroMemory(&Instructions, sizeof(Instructions)); }
    };

    struct Jump
    {
        POWERPC_INSTRUCTION Instructions[NUM_INSTRUCTIONS_IN_JUMP];

        Jump() { ZeroMemory(&Instructions, sizeof(Instructions)); }
    };

    void *m_pSource;
    const void *m_pDestination;
    size_t m_HookIndex;
    Jump m_Original;

    static Stub s_StubSection[MAX_HOOK_COUNT];
    static size_t s_HookCount;
    static CRITICAL_SECTION s_CriticalSection;

    void DetourFunctionStart();

    void PatchInJump(void *pSource, const void *pDestination, bool linked);

    void *ResolveBranch(POWERPC_INSTRUCTION instruction, const void *pBranch);

    void *GetModuleImport(const std::string &baseModuleName, const std::string &importedModuleName, uint32_t ordinal);
};

}
