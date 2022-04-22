#include "pch.h"
#include "Memory.h"

#include "Kernel.h"


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
    Kernel::ExCreateThread(nullptr, 0, nullptr, nullptr, pStartAddress, pParameters, dwCreationFlags);
}

}
