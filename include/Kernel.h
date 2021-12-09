#pragma once


namespace XexUtils
{
namespace Kernel
{

// Forgotten ppc intrinsic.
#define __isync() __emit(0x4C00012C)


// Imports from xboxkrnl.exe and xam.xex
extern "C"
{
    // Extended version of CreateThread from winbase.h.
    DWORD __stdcall ExCreateThread(
        LPHANDLE pHandle,
        DWORD dwStackSize,
        LPDWORD lpThreadId,
        LPVOID apiThreadStartup,
        LPTHREAD_START_ROUTINE lpStartAddress,
        LPVOID lpParameter,
        DWORD dwCreationFlagsMod
    );

    // Get the current title ID as a DWORD.
    DWORD XamGetCurrentTitleId();

    // Check if an address is accessible and writable.
    BOOL MmIsAddressValid(LPVOID address);
}

}
}
