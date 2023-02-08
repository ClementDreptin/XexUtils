#pragma once

#include "Xam_.h"

namespace XexUtils
{

class Memory
{
public:
    static void *ResolveFunction(const std::string &moduleName, uint32_t ordinal);

    static void Thread(PTHREAD_START_ROUTINE pStartAddress, void *pArgs = nullptr);

    static void ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pArgs, uint32_t creationFlags);

    template<typename T>
    static void Write(void *pDestination, T data)
    {
        if (!Xam::IsAddressValid(pDestination))
        {
            Log::Error("Invalid address: %p", pDestination);
            return;
        }

        *static_cast<T *>(pDestination) = data;
    }

    template<typename T>
    inline static void Write(uintptr_t address, T data) { Write<T>(reinterpret_cast<void *>(address), data); }

    template<typename T>
    static T Read(void *pSource)
    {
        if (!Xam::IsAddressValid(pSource))
        {
            Log::Error("Invalid address: %p", pSource);
            return 0;
        }

        return *static_cast<T *>(pSource);
    }

    template<typename T>
    inline static T Read(uintptr_t address) { return Read<T>(reinterpret_cast<void *>(address)); }
};

}
