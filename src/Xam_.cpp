#include "pch.h"
#include "Xam_.h"

#include "Memory.h"
#include "Formatter.h"


namespace XexUtils
{

// Create a pointer to XNotifyQueueUI in xam.xex

typedef void (*XNOTIFYQUEUEUI)(XNOTIFYQUEUEUI_TYPE dwType, DWORD dwUserIndex, unsigned long long qwAreas, const wchar_t *wszDisplayText, void *pContextData);
XNOTIFYQUEUEUI XNotifyQueueUI = reinterpret_cast<XNOTIFYQUEUEUI>(Memory::ResolveFunction("xam.xex", 656));

void Xam::XNotify(const std::string &strText, XNOTIFYQUEUEUI_TYPE dwType)
{
    XNotifyQueueUI(dwType, 0, XNOTIFY_SYSTEM, Formatter::ToWide(strText).c_str(), nullptr);
}

DWORD Xam::ShowKeyboard(const std::string &strTitle, const std::string &strDescription, const std::string &strDefaultValue, std::string &strResult, int nMaxLength, DWORD dwKeyboardType)
{
    // nMaxLength is the amount of characters the keyboard will allow, nRealMaxLength needs to include the \0 to terminate the string
    int nRealMaxLength = nMaxLength + 1;
    XOVERLAPPED Overlapped = {};

    // Create the buffers
    wchar_t *wszBuffer = new wchar_t[nRealMaxLength];
    char *szBuffer = new char[nRealMaxLength];

    // Zero the buffers
    ZeroMemory(wszBuffer, sizeof(wszBuffer));
    ZeroMemory(szBuffer, sizeof(szBuffer));

    // Open the keyboard
    XShowKeyboardUI(0, dwKeyboardType, Formatter::ToWide(strDefaultValue).c_str(), Formatter::ToWide(strTitle).c_str(), Formatter::ToWide(strDescription).c_str(), wszBuffer, nRealMaxLength, &Overlapped);

    // Wait until the keyboard closes
    while (!XHasOverlappedIoCompleted(&Overlapped))
        Sleep(100);

    // Get how the keyboard was closed (success, canceled or internal error)
    DWORD dwResult = XGetOverlappedResult(&Overlapped, nullptr, TRUE);
    if (dwResult == ERROR_SUCCESS)
    {
        // Convert the wide string to a narrow string
        wcstombs(szBuffer, wszBuffer, nRealMaxLength);

        // Populate the out string with the narrow string
        strResult = szBuffer;
    }

    // Cleanup
    delete[] wszBuffer;
    delete[] szBuffer;

    return dwResult;
}

}
