#pragma once

namespace XexUtils
{
namespace Memory
{
    DWORD ResolveFunction(const std::string& moduleName, DWORD ordinal);

    void Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters = 0);

    void HookFunctionStart(DWORD* address, DWORD* saveStub, DWORD destination);

    template<typename T>
    void Write(DWORD address, T data)
    {
        if (!Kernel::MmIsAddressValid((DWORD*)address))
        {
            Kernel::DbgPrint("Invalid address: %#010x\n", address);
            return;
        }

        *(T*)address = data;
    }

    template<typename T>
    T Read(DWORD address)
    {
        if (!Kernel::MmIsAddressValid((DWORD*)address))
        {
            Kernel::DbgPrint("Invalid address: %#010x\n", address);
            return 0;
        }

        return *(T*)address;
    }
}
}