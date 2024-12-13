#include "pch.h"
#include "Memory.h"

namespace XexUtils
{
namespace Memory
{

void *ResolveFunction(const std::string &moduleName, uint32_t ordinal)
{
    HMODULE moduleHandle = GetModuleHandle(moduleName.c_str());
    if (moduleHandle == nullptr)
        return nullptr;

    return GetProcAddress(moduleHandle, reinterpret_cast<const char *>(ordinal));
}

void Thread(PTHREAD_START_ROUTINE pStartAddress, void *pArgs)
{
    CreateThread(nullptr, 0, pStartAddress, pArgs, 0, nullptr);
}

void ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pArgs, EXCREATETHREAD_FLAG creationFlags)
{
    ExCreateThread(nullptr, 0, nullptr, nullptr, pStartAddress, pArgs, creationFlags);
}

}
}
