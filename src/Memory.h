#pragma once

#include "Xam_.h"

namespace XexUtils
{

// Utility static class with different memory manipulation functions.
class Memory
{
public:
    // Get a function in moduleName from its ordinal.
    static void *ResolveFunction(const std::string &moduleName, uint32_t ordinal);

    // Start a thread.
    static void Thread(PTHREAD_START_ROUTINE pStartAddress, void *pArgs = nullptr);

    // Start a thread with special creation flags.
    static void ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pArgs, uint32_t creationFlags);

    // Write data at pDestination
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

    // Write data at address.
    template<typename T>
    static void Write(uintptr_t address, T data)
    {
        Write<T>(reinterpret_cast<void *>(address), data);
    }

    // Read memory at pSource.
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

    // Read memory at address.
    template<typename T>
    static T Read(uintptr_t address)
    {
        return Read<T>(reinterpret_cast<void *>(address));
    }
};

}
