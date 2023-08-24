#pragma once

namespace XexUtils
{

class Hypervisor
{
public:
    template<typename T>
    static T Peek(uint64_t address)
    {
        void *pData = XPhysicalAlloc(sizeof(T), MAXULONG_PTR, 0, PAGE_READWRITE);
        Peek(address, pData, sizeof(T));
        T result = *reinterpret_cast<T *>(pData);
        XPhysicalFree(pData);

        return result;
    }

    template<typename T>
    static void Poke(uint64_t address, const T &data)
    {
        Poke(address, &data, sizeof(data));
    }

    static void Peek(uint64_t address, void *pDestination, size_t length);

    static void Poke(uint64_t address, const void *pSource, size_t length);

private:
    static uint64_t VirtualAddressToPhysicalAddress(const void *pAddress);

    static uint64_t HvxGetVersions(uint32_t key, uint64_t type, uint64_t sourceAddress, uint64_t destinationAddress, uint64_t length);
};

}
