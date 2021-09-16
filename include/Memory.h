#pragma once

namespace XexUtils
{
namespace Memory
{
    DWORD ResolveFunction(CONST std::string& moduleName, DWORD ordinal);

    VOID Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters = nullptr);

    VOID HookFunctionStart(LPDWORD address, LPDWORD saveStub, DWORD destination);

    template<typename T>
    VOID Write(DWORD address, T data)
    {
        if (!Kernel::MmIsAddressValid((LPDWORD)address))
        {
            Log::Error("Invalid address: %#010x", address);
            return;
        }

        *(T*)address = data;
    }

    template<typename T>
    T Read(DWORD address)
    {
        if (!Kernel::MmIsAddressValid((LPDWORD)address))
        {
            Log::Error("Invalid address: %#010x", address);
            return 0;
        }

        return *(T*)address;
    }
}
}
