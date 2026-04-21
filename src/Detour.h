#pragma once

#define MAX_DETOUR_COUNT 100
#define MAX_INSTRUCTIONS_IN_STUB 20

namespace XexUtils
{

/// @brief A class representing a function detour or hook.
class Detour
{
public:
    /// @brief Creates an empty `Detour`.
    Detour();

    /// @brief Creates a `Detour` from `pSource` to `pDestination`.
    /// @param pSource Where to detour.
    /// @param pDestination Where to make the detour go.
    Detour(void *pSource, const void *pDestination);

    /// @brief Creates a `Detour` from `sourceAddress` to `pDestination`.
    /// @param sourceAddress Where to detour.
    /// @param pDestination Where to make the detour go.
    Detour(uintptr_t sourceAddress, const void *pDestination);

    /// @brief Creates a `Detour` from the `ordinal`th function exported by `moduleName`
    /// to `pDestination`.
    /// @param moduleName The name of the module.
    /// @param ordinal The ordinal of the function to detour.
    /// @param pDestination Where the make the detour go.
    Detour(const std::string &moduleName, uint32_t ordinal, const void *pDestination);

    /// @brief Creates a `Detour` from the `ordinal`th function exported by
    /// `importedModuleName` used by `moduleName` to `pDestination`.
    /// @param moduleName The name of the module importing the function.
    /// @param importedModuleName The name of the module from which the function is exported.
    /// @param ordinal The ordinal of the function to detour.
    /// @param pDestination Where the make the detour go.
    Detour(const std::string &moduleName, const std::string &importedModuleName, uint32_t ordinal, const void *pDestination);

    /// @brief Calls `Remove`.
    ~Detour();

    /// @brief Sets up the detour from the source to the destination.
    ///
    /// This function can fail if the total amount of detours exceeds `MAX_DETOUR_COUNT`,
    /// or if either the source or the destination are `nullptr`.
    ///
    /// @return `S_OK` on success, `E_FAIL` on error.
    HRESULT Install();

    /// @brief Restores the original behavior at the source.
    void Remove();

    /// @brief Gets a function pointer to the original function, before the detour.
    /// @tparam T The function pointer type to return.
    /// @return A function pointer of type `T`.
    template<typename T>
    __declspec(noinline) T GetOriginal() const
    {
        return reinterpret_cast<T>(&s_Stubs[m_SlotIndex]);
    }

private:
    typedef uint32_t POWERPC_INSTRUCTION;

    struct Original
    {
        POWERPC_INSTRUCTION Instructions[4];

        Original() { ZeroMemory(this, sizeof(*this)); }
    };

    struct Jump
    {
        POWERPC_INSTRUCTION Instructions[6];
        size_t Size;

        Jump(const void *pTarget, bool linked = false, bool preserveR0 = false, uint32_t branchOptions = 20 /* BRANCH_OPTIONS_ALWAYS */, uint8_t conditionRegisterBit = 0);

        void Write(void *pDestination);
    };

    void *m_pSource;
    const void *m_pDestination;
    size_t m_SlotIndex;
    Original m_Original;

    void DetourFunctionStart();

    Jump RelocateBranch(const void *pLocation);

    void *GetModuleImport(const std::string &baseModuleName, const std::string &importedModuleName, uint32_t ordinal);

private:
    static POWERPC_INSTRUCTION s_Stubs[MAX_DETOUR_COUNT][MAX_INSTRUCTIONS_IN_STUB];
    static bool Detour::s_UsedSlots[MAX_DETOUR_COUNT];
    static CRITICAL_SECTION s_CriticalSection;
};

}
