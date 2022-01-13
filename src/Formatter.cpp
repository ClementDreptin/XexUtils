#include "pch.h"
#include "Formatter.h"


namespace XexUtils
{

std::string Formatter::Format(const std::string& strMessage, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, strMessage);

    const int MAX_SIZE = 2048;

    // Build the string with the format
    char szBuffer[MAX_SIZE] = { 0 };
    vsnprintf_s(szBuffer, _TRUNCATE, strMessage.c_str(), pArgList);

    // Free the variadic arguments
    va_end(pArgList);

    return std::string(szBuffer);
}

std::wstring Formatter::ToWide(const std::string &strNarrowString)
{
    // Create the wide string
    std::wstring wstrWideString;

    // Copy the narrow string into the wide string from start to end
    wstrWideString.assign(strNarrowString.begin(), strNarrowString.end());

    return wstrWideString;
}

}
