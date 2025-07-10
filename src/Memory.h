#pragma once

#include "Kernel.h"
#include "Xam.h"

namespace XexUtils
{
namespace Memory
{

/// @brief Gets a pointer to the `ordinal`th function exported by `moduleName`.
///
/// This function can fail if no module with the name `moduleName` is currently loaded,
/// or if `ordinal` is greater than the amount of functions exported by `moduleName`.
///
/// @param moduleName The name of the module.
/// @param ordinal The ordinal number of the function.
/// @return A generic `void *` to the function on success, `nullptr` on error.
void *ResolveFunction(const std::string &moduleName, uint32_t ordinal);

/// @brief Simple wrapper around `CreateThread` to only pass a function and its arguments.
/// @param pStartAddress A pointer to the function to run in a separate thread.
/// @param pArgs A pointer to the arguments to pass to the function at `pStartAddress`.
/// @return The `HANDLE` of the newly created thread.
HANDLE Thread(PTHREAD_START_ROUTINE pStartAddress, void *pArgs = nullptr);

/// @brief Simple wrapper around `ExCreateThread` to pass less arguments.
/// @param pStartAddress A pointer to the function to run in a separate thread.
/// @param pArgs A pointer to the arguments to pass to the function at `pStartAddress`.
/// @param creationFlags The thread creation flags.
/// @param pThreadId A pointer to a `uint32_t` to store the thread ID.
/// @return The `HANDLE` of the newly created thread.
HANDLE ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void *pArgs, EXCREATETHREAD_FLAG creationFlags, uint32_t *pThreadId = nullptr);

/// @brief Safely writes an instance of `T` at `pDestination` (without access violations).
/// @tparam T The type of data to write.
/// @param pDestination A pointer to where to write `data`.
/// @param data The instance of `T` to write.
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

/// @brief Safely writes an instance of `T` at `address` (without access violations).
/// @tparam T The type of data to write.
/// @param address Where to write `data`.
/// @param data The instance of `T` to write.
template<typename T>
inline void Write(uintptr_t address, const T &data)
{
    Write<T>(reinterpret_cast<void *>(address), data);
}

/// @brief Safely reads an instance of `T` at `pSource` (without access violations).
/// @tparam T The type of data to read.
/// @param pSource A pointer to where to read.
/// @return An instance of `T` copied from `pSource`.
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

/// @brief Safely reads an instance of `T` at `address` (without access violations).
/// @tparam T The type of data to read.
/// @param address Where to read.
/// @return An instance of `T` copied from `address`.
template<typename T>
inline T Read(uintptr_t address)
{
    return Read<T>(reinterpret_cast<void *>(address));
}

}
}
