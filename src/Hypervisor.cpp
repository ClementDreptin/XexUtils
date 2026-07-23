#include "pch.h"
#include "Hypervisor.h"

#include "Kernel.h"

// Most of this logic was inspired by this:
// https://codeberg.org/hax360/ExShadowBoot/src/branch/main/ExShadowBoot/Freeboot.h

namespace XexUtils
{
namespace Hypervisor
{

#pragma warning(push)
#pragma warning(disable : 4826) // Conversion from 'void *' to 'uint64_t' is sign-extended

static uint64_t VirtualAddressToPhysicalAddress(const void *pAddress)
{
    XASSERT(pAddress != nullptr);

    return 0x8000000000000000 + reinterpret_cast<uint64_t>(MmGetPhysicalAddress(const_cast<void *>(pAddress)));
}

#pragma warning(pop)

static const uint32_t s_FreebootBackdoorKey = 0x72627472;

typedef enum _FreebootBackdoorType
{
    FreebootBackdoorType_DisableMemoryProtections = 2,
    FreebootBackdoorType_EnableMemoryProtections,
    FreebootBackdoorType_Execute,
    FreebootBackdoorType_Memcpy
} FreebootBackdoorType;

static uint64_t __declspec(naked) HvxFreebootBackdoor(uint32_t key, uint64_t type, uint64_t sourceAddress, uint64_t destinationAddress, uint64_t length)
{
    // The Freeboot backdoor is in syscall number 0 (normally HvxGetVersions)
    __asm
    {
        li r0, 0x0
        sc
        blr
    }
}

// Note: memory at pDestination HAS to be allocated with XPhysicalAlloc and not just malloc
void Peek(uint64_t address, void *pDestination, size_t length)
{
    XASSERT(address != 0);
    XASSERT(pDestination != nullptr);

    uint64_t destination = VirtualAddressToPhysicalAddress(pDestination);
    HvxFreebootBackdoor(s_FreebootBackdoorKey, FreebootBackdoorType_Memcpy, address, destination, length);
}

void Poke(uint64_t address, const void *pSource, size_t length)
{
    XASSERT(address != 0);
    XASSERT(pSource != nullptr);

    uint64_t source = VirtualAddressToPhysicalAddress(pSource);
    HvxFreebootBackdoor(s_FreebootBackdoorKey, FreebootBackdoorType_Memcpy, source, address, length);
}

void EnableMemoryProtections()
{
    HvxFreebootBackdoor(s_FreebootBackdoorKey, FreebootBackdoorType_EnableMemoryProtections, 0, 0, 0);
}

void DisableMemoryProtections()
{
    HvxFreebootBackdoor(s_FreebootBackdoorKey, FreebootBackdoorType_DisableMemoryProtections, 0, 0, 0);
}

}
}
