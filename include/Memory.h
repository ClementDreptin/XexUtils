#pragma once

#include "Xam_.h"


namespace XexUtils
{

// Utility static class with different memory manipulation functions.
class Memory
{
public:
    // Get a function in strModuleName from its ordinal.
    static DWORD ResolveFunction(const std::string &strModuleName, DWORD dwOrdinal);

    // Start a thread.
    static void Thread(PTHREAD_START_ROUTINE pStartAddress, void *pParameters = nullptr);

    // Start a thread with special creation flags.
    static void ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pParameters, DWORD dwCreationFlags);

    // Write data at dwAddress.
    template<typename T>
    static void Write(DWORD dwAddress, T data)
    {
        if (!Xam::IsAddressValid(reinterpret_cast<DWORD *>(dwAddress)))
        {
            Log::Error("Invalid address: %#010x", dwAddress);
            return;
        }

        *reinterpret_cast<T *>(dwAddress) = data;
    }

    // Read memory at dwAddress.
    template<typename T>
    static T Read(DWORD dwAddress)
    {
        if (!Xam::IsAddressValid(reinterpret_cast<DWORD *>(dwAddress)))
        {
            Log::Error("Invalid address: %#010x", dwAddress);
            return 0;
        }

        return *reinterpret_cast<T *>(dwAddress);
    }
};

}
