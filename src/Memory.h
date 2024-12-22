#pragma once

#include "Kernel.h"
#include "Xam_.h"

namespace XexUtils
{
namespace Memory
{

void *ResolveFunction(const std::string &moduleName, uint32_t ordinal);

void Thread(PTHREAD_START_ROUTINE pStartAddress, void *pArgs = nullptr);

void ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pArgs, EXCREATETHREAD_FLAG creationFlags);

template<typename T>
void Write(void *pDestination, const T &data)
{
    if (pDestination == nullptr || !Xam::IsAddressValid(pDestination))
    {
        Log::Error("Invalid address: %p", pDestination);
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
        Log::Error("Invalid address: %p", pSource);
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
