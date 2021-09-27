#pragma once


namespace XexUtils
{

//--------------------------------------------------------------------------------------
// Name: class Memory
// Desc: Utility static class with different memory manipulation functions.
//--------------------------------------------------------------------------------------
class Memory
{
public:
    static DWORD ResolveFunction(CONST std::string& strModuleName, DWORD dwOrdinal);
    static VOID Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters = nullptr);
    static VOID ThreadEx(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters, DWORD dwCreationFlags);
    static VOID HookFunctionStart(LPDWORD lpdwAddress, LPDWORD lpdwSaveStub, DWORD dwDestination);

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
    static VOID PatchInJump(LPDWORD lpdwAddress, DWORD dwDestination, BOOL bLinked);
    static VOID GLPR();
    static DWORD RelinkGPLR(INT nOffset, LPDWORD lpdwSaveStubAddr, LPDWORD lpdwOrgAddr);
};

}
