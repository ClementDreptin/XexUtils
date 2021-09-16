#pragma once

namespace XexUtils
{
namespace Kernel
{
    extern "C"
    {
        DWORD __stdcall ExCreateThread(
            LPHANDLE pHandle,
            DWORD dwStackSize,
            LPDWORD lpThreadId,
            LPVOID apiThreadStartup,
            LPTHREAD_START_ROUTINE lpStartAddress,
            LPVOID lpParameter,
            DWORD dwCreationFlagsMod
        );

        DWORD XamGetCurrentTitleId();

        BOOL MmIsAddressValid(LPVOID address);

        #define __isync() __emit(0x4C00012C)
    }
}
}
