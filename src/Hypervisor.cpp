#include "pch.h"
#include "Hypervisor.h"

#include "Kernel.h"

#define MAGIC 0x72627472
#define TYPE 5 // I don't what 5 means

namespace XexUtils
{

// Note: memory at pDestination HAS to be allocated with XPhysicalAlloc and not just malloc
void Hypervisor::Peek(uint64_t address, void *pDestination, size_t length)
{
    uint64_t destination = VirtualAddressToPhysicalAddress(pDestination);
    HvxGetVersions(MAGIC, TYPE, address, destination, length);
}

void Hypervisor::Poke(uint64_t address, const void *pSource, size_t length)
{
    uint64_t source = VirtualAddressToPhysicalAddress(pSource);
    HvxGetVersions(MAGIC, TYPE, source, address, length);
}

#pragma warning(push)
#pragma warning(disable : 4826) // Conversion from 'void *' to 'uint64_t' is sign-extended

uint64_t Hypervisor::VirtualAddressToPhysicalAddress(const void *pAddress)
{
    return 0x8000000000000000 + reinterpret_cast<uint64_t>(MmGetPhysicalAddress(const_cast<void *>(pAddress)));
}

#pragma warning(pop)

uint64_t __declspec(naked) Hypervisor::HvxGetVersions(uint32_t key, uint64_t type, uint64_t sourceAddress, uint64_t destinationAddress, uint64_t length)
{
    // Execute syscall number 0
    // syscalls table: https://www.xenonwiki.com/System_Calls
    __asm
    {
        li r0, 0x0
        sc
        blr
    }
}

}
