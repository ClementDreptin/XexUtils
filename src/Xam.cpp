#include "pch.h"
#include "Xam.h"

#include "Formatter.h"
#include "Kernel.h"
#include "Memory.h"

namespace XexUtils
{
namespace Xam
{

// Create a pointer to XNotifyQueueUI in xam.xex

typedef void (*XNOTIFYQUEUEUI)(XNOTIFYQUEUEUI_TYPE type, uint32_t userIndex, uint64_t areas, const wchar_t *displayText, void *pContextData);
static XNOTIFYQUEUEUI XNotifyQueueUI = static_cast<XNOTIFYQUEUEUI>(Memory::ResolveFunction("xam.xex", 656));

void XNotify(const std::string &text, XNOTIFYQUEUEUI_TYPE type)
{
    XNotifyQueueUI(type, 0, XNOTIFY_SYSTEM, Formatter::ToWide(text).c_str(), nullptr);
}

uint32_t ShowKeyboard(const std::wstring &title, const std::wstring &description, const std::wstring &defaultText, std::string &result, size_t maxLength, uint32_t keyboardType)
{
    // maxLength is the amount of characters the keyboard will allow, realMaxLength needs to include the \0 to terminate the string
    size_t realMaxLength = maxLength + 1;
    XOVERLAPPED overlapped = {};

    // Create the buffers
    std::unique_ptr<wchar_t[]> wideBuffer(new wchar_t[realMaxLength]);
    std::unique_ptr<char[]> buffer(new char[realMaxLength]);

    // Zero the buffers
    ZeroMemory(wideBuffer.get(), sizeof(wideBuffer));
    ZeroMemory(buffer.get(), sizeof(buffer));

    // Open the keyboard
    XShowKeyboardUI(
        0,
        keyboardType,
        defaultText.c_str(),
        title.c_str(),
        description.c_str(),
        wideBuffer.get(),
        realMaxLength,
        &overlapped
    );

    // Wait until the keyboard closes
    while (!XHasOverlappedIoCompleted(&overlapped))
        Sleep(100);

    // Get how the keyboard was closed (success, canceled or internal error)
    uint32_t overlappedResult = XGetOverlappedResult(&overlapped, nullptr, TRUE);
    if (overlappedResult == ERROR_SUCCESS)
    {
        // Convert the wide string to a narrow string
        wcstombs_s(nullptr, buffer.get(), realMaxLength, wideBuffer.get(), realMaxLength * sizeof(wchar_t));

        // Populate the out string with the narrow string
        result = buffer.get();
    }

    return overlappedResult;
}

uint32_t ShowMessageBox(const std::wstring &title, const std::wstring &text, const std::vector<std::wstring> &buttonLabels, uint32_t messageBoxType, uint32_t *pButtonPressedIndex, uint32_t focusedButtonIndex)
{
    MESSAGEBOX_RESULT messageBoxResult = {};
    XOVERLAPPED overlapped = {};

    // Create the vector of const wchar_t * from the vector of std::wstring
    std::vector<const wchar_t *> cbuttonLabels;
    cbuttonLabels.reserve(buttonLabels.size());
    for (size_t i = 0; i < buttonLabels.size(); i++)
        cbuttonLabels.push_back(buttonLabels[i].c_str());

    // Open the message box
    XShowMessageBoxUI(
        0,
        title.c_str(),
        text.c_str(),
        cbuttonLabels.size(),
        cbuttonLabels.data(),
        focusedButtonIndex,
        messageBoxType,
        &messageBoxResult,
        &overlapped
    );

    // Wait until the message box closes
    while (!XHasOverlappedIoCompleted(&overlapped))
        Sleep(100);

    // Get how the message box was closed (success, canceled or internal error)
    uint32_t overlappedResult = XGetOverlappedResult(&overlapped, nullptr, TRUE);

    // If the message box was closed by pressing "A" on any of the buttons (so not by pressing "B" or the Xbox button)
    // and if the pressed button is requested, write the pressed button at pButtonPressedIndex
    if (overlappedResult == ERROR_SUCCESS && pButtonPressedIndex != nullptr)
        *pButtonPressedIndex = messageBoxResult.dwButtonPressed;

    return overlappedResult;
}

uint32_t GetCurrentTitleId()
{
    return XamGetCurrentTitleId();
}

bool IsAddressValid(const void *pAddress)
{
    return MmIsAddressValid(const_cast<void *>(pAddress));
}

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
