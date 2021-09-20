#pragma once


namespace XexUtils
{
namespace Kernel
{

// Forgotten ppc intrinsic
#define __isync() __emit(0x4C00012C)


// Imports from xboxkrnl.exe and xam.xex
extern "C"
{
    //--------------------------------------------------------------------------------------
    // Name: ExCreateThread()
    // Desc: Extended version of CreateThread from winbase.h.
    //--------------------------------------------------------------------------------------
    DWORD __stdcall ExCreateThread(
        LPHANDLE pHandle,
        DWORD dwStackSize,
        LPDWORD lpThreadId,
        LPVOID apiThreadStartup,
        LPTHREAD_START_ROUTINE lpStartAddress,
        LPVOID lpParameter,
        DWORD dwCreationFlagsMod
    );


    //--------------------------------------------------------------------------------------
    // Name: XamGetCurrentTitleId
    // Desc: Get the current title ID as a DWORD.
    //--------------------------------------------------------------------------------------
    DWORD XamGetCurrentTitleId();


    //--------------------------------------------------------------------------------------
    // Name: MmIsAddressValid
    // Desc: Check if an address is accessible and writable.
    //--------------------------------------------------------------------------------------
    BOOL MmIsAddressValid(LPVOID address);
}

}
}
