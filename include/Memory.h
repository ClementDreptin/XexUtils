#pragma once


namespace XexUtils
{

// Utility static class with different memory manipulation functions.
class Memory
{
public:
    // Get a function in strModuleName from its ordinal.
    static DWORD ResolveFunction(const std::string &strModuleName, DWORD dwOrdinal);

    // Start a thread.
    static void Thread(PTHREAD_START_ROUTINE pStartAddress, void *pParameters = nullptr);

    // Start a thread with special creation flags.
    static void ThreadEx(LPTHREAD_START_ROUTINE pStartAddress, void *pParameters, DWORD dwCreationFlags);

    // Hook a function.
    static void HookFunctionStart(DWORD *pdwAddress, DWORD *pdwSaveStub, DWORD dwDestination);

    // Write data at dwAddress.
    template<typename T>
    static void Write(DWORD dwAddress, T data)
    {
        if (!Kernel::MmIsAddressValid(reinterpret_cast<DWORD *>(dwAddress)))
        {
            Log::Error("Invalid address: %#010x", dwAddress);
            return;
        }

        *(T *)dwAddress = data;
    }

    // Read memory at dwAddress.
    template<typename T>
    static T Read(DWORD dwAddress)
    {
        if (!Kernel::MmIsAddressValid(reinterpret_cast<DWORD *>(dwAddress)))
        {
            Log::Error("Invalid address: %#010x", dwAddress);
            return 0;
        }

        return *(T *)dwAddress;
    }
private:
    // Insert a jump instruction into an existing function to jump to another function.
    static void PatchInJump(DWORD *pdwAddress, DWORD dwDestination, bool bLinked);

    static void GLPR();

    static DWORD RelinkGPLR(int nOffset, DWORD *pdwSaveStubAddr, DWORD *pdwOrgAddr);
};

}
