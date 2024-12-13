#include "pch.h"
#include "Hypervisor.h"

#include "Kernel.h"

namespace XexUtils
{
namespace Hypervisor
{

#pragma warning(push)
#pragma warning(disable : 4826) // Conversion from 'void *' to 'uint64_t' is sign-extended

static uint64_t VirtualAddressToPhysicalAddress(const void *pAddress)
{
    return 0x8000000000000000 + reinterpret_cast<uint64_t>(MmGetPhysicalAddress(const_cast<void *>(pAddress)));
}

#pragma warning(pop)

static uint64_t __declspec(naked) HvxGetVersions(uint32_t key, uint64_t type, uint64_t sourceAddress, uint64_t destinationAddress, uint64_t length)
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

#define MAGIC 0x72627472
#define TYPE 5 // I don't what 5 means

// Note: memory at pDestination HAS to be allocated with XPhysicalAlloc and not just malloc
void Peek(uint64_t address, void *pDestination, size_t length)
{
    uint64_t destination = VirtualAddressToPhysicalAddress(pDestination);
    HvxGetVersions(MAGIC, TYPE, address, destination, length);
}

void Poke(uint64_t address, const void *pSource, size_t length)
{
    uint64_t source = VirtualAddressToPhysicalAddress(pSource);
    HvxGetVersions(MAGIC, TYPE, source, address, length);
}

}
}
