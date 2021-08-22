#include "pch.h"
#include "Xam_.h"

#include "Memory.h"
#include "Formatter.h"

namespace XexUtils
{
namespace Xam
{
    typedef void (*XNOTIFYQUEUEUI)(XNOTIFYQUEUEUI_TYPE exnq, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData);
    XNOTIFYQUEUEUI XNotifyQueueUI = (XNOTIFYQUEUEUI)Memory::ResolveFunction("xam.xex", 656);

    void XNotify(const std::string& text, XNOTIFYQUEUEUI_TYPE type)
    {
        XNotifyQueueUI(type, 0, XNOTIFY_SYSTEM, (PWCHAR)(Formatter::ToWide(text).c_str()), nullptr);
    }

    std::string ShowKeyboard(const std::string& title, const std::string& description, const std::string& defaultValue, size_t maxLength, DWORD keyboardType)
    {
        // maxLength is the amount of characters the keyboard will allow, realMaxLength needs to include the \0 to terminate the string
        size_t realMaxLength = maxLength + 1;
        XOVERLAPPED overlapped;
        wchar_t* wideBuffer = new wchar_t[realMaxLength];
        char* buffer = new char[realMaxLength];

        ZeroMemory(&overlapped, sizeof(overlapped));
        XShowKeyboardUI(0, keyboardType, Formatter::ToWide(defaultValue).c_str(), Formatter::ToWide(title).c_str(), Formatter::ToWide(description).c_str(), wideBuffer, realMaxLength, &overlapped);

        while (!XHasOverlappedIoCompleted(&overlapped))
            Sleep(100);

        wcstombs(buffer, wideBuffer, realMaxLength);

        std::string result = buffer;

        delete[] wideBuffer;
        delete[] buffer;

        return result;
    }
}
}