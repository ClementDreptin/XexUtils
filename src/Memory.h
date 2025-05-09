#pragma once

#include "Kernel.h"
#include "Xam_.h"

namespace XexUtils
{
namespace Memory
{

void *ResolveFunction(const std::string &moduleName, uint32_t ordinal);

HANDLE Thread(PTHREAD_START_ROUTINE pStartAddress, void *pArgs = nullptr);

HANDLE ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pArgs, EXCREATETHREAD_FLAG creationFlags, uint32_t *pThreadId = nullptr);

template<typename T>
void Write(void *pDestination, const T &data)
{
    if (pDestination == nullptr || !Xam::IsAddressValid(pDestination))
    {
        DebugPrint("[XexUtils][Memory]: Error: Invalid address: %p.", pDestination);
        return;
    }

    *static_cast<T *>(pDestination) = data;
}

template<typename T>
inline void Write(uintptr_t address, const T &data)
{
    Write<T>(reinterpret_cast<void *>(address), data);
}

template<typename T>
inline T Read(void *pSource)
{
    if (pSource == nullptr || !Xam::IsAddressValid(pSource))
    {
        DebugPrint("[XexUtils][Memory]: Error: Invalid address: %p.", pSource);
        return T();
    }

    return *static_cast<T *>(pSource);
}

template<typename T>
inline T Read(uintptr_t address)
{
    return Read<T>(reinterpret_cast<void *>(address));
}

}
}
