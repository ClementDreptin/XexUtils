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

void *Memory::ResolveFunction(const std::string &moduleName, uint32_t ordinal)
{
    HMODULE hModule = GetModuleHandle(moduleName.c_str());

    return (hModule == NULL) ? NULL : GetProcAddress(hModule, reinterpret_cast<const char *>(ordinal));
}

void Memory::Thread(PTHREAD_START_ROUTINE pStartAddress, void *pArgs)
{
    CreateThread(nullptr, 0, pStartAddress, pArgs, 0, nullptr);
}

void Memory::ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pArgs, uint32_t creationFlags)
{
    ExCreateThread(nullptr, 0, nullptr, nullptr, pStartAddress, pArgs, creationFlags);
}

}
