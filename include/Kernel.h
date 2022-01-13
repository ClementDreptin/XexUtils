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
        HANDLE *pHandle,
        DWORD dwStackSize,
        DWORD *pThreadId,
        void *apiThreadStartup,
        PTHREAD_START_ROUTINE pStartAddress,
        void *pParameter,
        DWORD dwCreationFlagsMod
    );

    // Get the current title ID as a DWORD.
    DWORD XamGetCurrentTitleId();

    // Check if an address is accessible and writable.
    bool MmIsAddressValid(void *pAddress);
}

}
}
