#pragma once

namespace XexUtils
{
namespace Hypervisor
{

template<typename T>
T Peek(uint64_t address)
{
    void *pData = XPhysicalAlloc(sizeof(T), MAXULONG_PTR, 0, PAGE_READWRITE);
    Peek(address, pData, sizeof(T));
    T result = *reinterpret_cast<T *>(pData);
    XPhysicalFree(pData);

    return result;
}

template<typename T>
void Poke(uint64_t address, const T &data)
{
    Poke(address, &data, sizeof(data));
}

void Peek(uint64_t address, void *pDestination, size_t length);

void Poke(uint64_t address, const void *pSource, size_t length);

}
}
