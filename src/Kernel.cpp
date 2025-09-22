#include "pch.h"
#include "Kernel.h"

#include "Memory.h"

namespace XexUtils
{
namespace Kernel
{

void Reboot()
{
    HalReturnToFirmware(HalRebootRoutine);
}

HRESULT MountPath(const std::string &linkName, const std::string &devicePath)
{
    // The system only allows executables to access the directory they live in and binds it to
    // the "game:" drive. Nothing else is accessible unless you create a symbolic link.

    STRING link = {};
    STRING device = {};
    std::string userDestinationDrive = "\\??\\" + linkName;
    std::string systemDestinationDrive = "\\System??\\" + linkName;

    // Initialize the STRING structs
    if (KeGetCurrentProcessType() == PROC_SYSTEM)
        RtlInitAnsiString(&link, systemDestinationDrive.c_str());
    else
        RtlInitAnsiString(&link, userDestinationDrive.c_str());

    RtlInitAnsiString(&device, devicePath.c_str());

    // Bind devicePath to the linkName.
    return ObCreateSymbolicLink(&link, &device);
}

HRESULT MountHdd()
{
    return MountPath("hdd:", "\\Device\\Harddisk0\\Partition1\\");
}

HRESULT MountUsb()
{
    return MountPath("usb:", "\\Device\\Mass0\\");
}

HRESULT UnmountPath(const std::string &linkName)
{
    STRING link = {};
    std::string userDestinationDrive = "\\??\\" + linkName;
    std::string systemDestinationDrive = "\\System??\\" + linkName;

    // Initialize the STRING structs
    if (KeGetCurrentProcessType() == PROC_SYSTEM)
        RtlInitAnsiString(&link, systemDestinationDrive.c_str());
    else
        RtlInitAnsiString(&link, userDestinationDrive.c_str());

    // Remove the symbolic link
    return ObDeleteSymbolicLink(&link);
}

HRESULT UnmountHdd()
{
    return UnmountPath("hdd:");
}

HRESULT UnmountUsb()
{
    return UnmountPath("usb:");
}

bool IsDevkit()
{
    // Read a 32-bit unsigned int at 0x8E038610 and if the 16th is NOT set, the console is a devkit.
    // This bit is not set while running in Xenia so make sure that's not the case
    return !(Memory::Read<uint32_t>(0x8E038610) & (1 << 15)) && !InXenia();
}

bool InXenia()
{
    // Inspired by this
    // https://github.com/RBEnhanced/RB3Enhanced/blob/master/source/xbox360.c#L16

    void *xamFirstExport = Memory::ResolveFunction("xam.xex", 1);
#ifndef NDEBUG
    if (xamFirstExport == nullptr)
        DebugPrint("[XexUtils][Xam]: Error: Could not find the first function exported by xam.xex, this should not happen.");
#endif

    // If Xam is not in the typical memory address space, we're in an emulator
    return reinterpret_cast<uintptr_t>(xamFirstExport) >> 24 != 0x81;
}

}
}
