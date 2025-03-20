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
    {
        DebugPrint("[XexUtils][Memory]: Error: Could find module %s. Make sure it is loaded.", moduleName.c_str());
        return nullptr;
    }

    return GetProcAddress(moduleHandle, reinterpret_cast<const char *>(ordinal));
}

HANDLE Thread(PTHREAD_START_ROUTINE pStartAddress, void *pArgs)
{
    return CreateThread(nullptr, 0, pStartAddress, pArgs, 0, nullptr);
}

HANDLE ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pArgs, EXCREATETHREAD_FLAG creationFlags, uint32_t *pThreadId)
{
    HANDLE handle = nullptr;
    ExCreateThread(&handle, 0, pThreadId, nullptr, pStartAddress, pArgs, creationFlags);

    return handle;
}

}
}
