#include "pch.h"
#include "Xam_.h"

#include "Memory.h"
#include "Formatter.h"


namespace XexUtils
{

// Create a pointer to XNotifyQueueUI in xam.xex
typedef VOID (*XNOTIFYQUEUEUI)(XNOTIFYQUEUEUI_TYPE dwType, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR wszDisplayText, LPVOID pContextData);
XNOTIFYQUEUEUI XNotifyQueueUI = (XNOTIFYQUEUEUI)Memory::ResolveFunction("xam.xex", 656);

VOID Xam::XNotify(CONST std::string& strText, XNOTIFYQUEUEUI_TYPE dwType)
{
    XNotifyQueueUI(dwType, 0, XNOTIFY_SYSTEM, (PWCHAR)(Formatter::ToWide(strText).c_str()), nullptr);
}

std::string Xam::ShowKeyboard(CONST std::string& strTitle, CONST std::string& strDescription, CONST std::string& strDefaultValue, INT nMaxLength, DWORD dwKeyboardType)
{
    // nMaxLength is the amount of characters the keyboard will allow, nRealMaxLength needs to include the \0 to terminate the string
    INT nRealMaxLength = nMaxLength + 1;
    XOVERLAPPED overlapped;

    // Create the buffers
    PWCHAR wszBuffer = new WCHAR[nRealMaxLength];
    LPSTR szBuffer = new CHAR[nRealMaxLength];

    // Zero the buffers and structs
    ZeroMemory(&overlapped, sizeof(XOVERLAPPED));
    ZeroMemory(wszBuffer, sizeof(wszBuffer));
    ZeroMemory(szBuffer, sizeof(szBuffer));

    // Open the keyboard
    XShowKeyboardUI(0, dwKeyboardType, Formatter::ToWide(strDefaultValue).c_str(), Formatter::ToWide(strTitle).c_str(), Formatter::ToWide(strDescription).c_str(), wszBuffer, nRealMaxLength, &overlapped);

    // Wait until the keyboard closes
    while (!XHasOverlappedIoCompleted(&overlapped))
        Sleep(100);

    // Convert the wide string to a narrow string
    wcstombs(szBuffer, wszBuffer, nRealMaxLength);

    std::string result = szBuffer;

    // Cleanup
    delete[] wszBuffer;
    delete[] szBuffer;

    return result;
}

}
