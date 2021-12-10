#pragma once


namespace XexUtils
{

// Utility static class with different memory manipulation functions.
class Memory
{
public:
    // Get a function in strModuleName from its ordinal.
    static DWORD ResolveFunction(CONST std::string &strModuleName, DWORD dwOrdinal);

    // Start a thread.
    static VOID Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters = nullptr);

    // Start a thread with special creation flags.
    static VOID ThreadEx(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters, DWORD dwCreationFlags);

    // Hook a function.
    static VOID HookFunctionStart(LPDWORD lpdwAddress, LPDWORD lpdwSaveStub, DWORD dwDestination);

    // Write data at dwAddress.
    template<typename T>
    static VOID Write(DWORD dwAddress, T data)
    {
        if (!Kernel::MmIsAddressValid((LPDWORD)dwAddress))
        {
            Log::Error("Invalid address: %#010x", dwAddress);
            return;
        }

        *(T*)dwAddress = data;
    }

    // Read memory at dwAddress.
    template<typename T>
    static T Read(DWORD dwAddress)
    {
        if (!Kernel::MmIsAddressValid((LPDWORD)dwAddress))
        {
            Log::Error("Invalid address: %#010x", dwAddress);
            return 0;
        }

        return *(T*)dwAddress;
    }
private:
    // Insert a jump instruction into an existing function to jump to another function.
    static VOID PatchInJump(LPDWORD lpdwAddress, DWORD dwDestination, BOOL bLinked);

    static VOID GLPR();

    static DWORD RelinkGPLR(INT nOffset, LPDWORD lpdwSaveStubAddr, LPDWORD lpdwOrgAddr);
};

}
