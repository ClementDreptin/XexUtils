#include "pch.h"
#include "Memory.h"


// Import from xboxkrnl.exe
extern "C"
{
    DWORD __stdcall ExCreateThread(
        HANDLE *pHandle,
        DWORD dwStackSize,
        DWORD *pThreadId,
        void *apiThreadStartup,
        PTHREAD_START_ROUTINE pStartAddress,
        void *pParameter,
        DWORD dwCreationFlagsMod
    );
}


namespace XexUtils
{

DWORD Memory::ResolveFunction(const std::string &strModuleName, DWORD dwOrdinal)
{
    HMODULE hModule = GetModuleHandle(strModuleName.c_str());

    return (hModule == NULL) ? NULL : reinterpret_cast<DWORD>(GetProcAddress(hModule, reinterpret_cast<const char *>(dwOrdinal)));
}

void Memory::Thread(PTHREAD_START_ROUTINE pStartAddress, void *pParameters)
{
    CreateThread(nullptr, 0, pStartAddress, pParameters, 0, nullptr);
}

void Memory::ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pParameters, DWORD dwCreationFlags)
{
    ExCreateThread(nullptr, 0, nullptr, nullptr, pStartAddress, pParameters, dwCreationFlags);
}

}
