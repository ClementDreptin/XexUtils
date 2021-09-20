#include "pch.h"
#include "Formatter.h"


namespace XexUtils
{

//--------------------------------------------------------------------------------------
// Name: Format()
// Desc: Format a string in with a printf-like format.
//--------------------------------------------------------------------------------------
std::string Formatter::Format(CONST std::string& strMessage, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, strMessage);

    CONST INT MAX_SIZE = 2048;

    // Build the string with the format
    CHAR szBuffer[MAX_SIZE] = { 0 };
    vsnprintf_s(szBuffer, _TRUNCATE, strMessage.c_str(), pArgList);

    // Free the variadic arguments
    va_end(pArgList);

    return std::string(szBuffer);
}


//--------------------------------------------------------------------------------------
// Name: ToWide()
// Desc: Create a wide string from a narrow string.
//--------------------------------------------------------------------------------------
std::wstring Formatter::ToWide(CONST std::string& strNarrowString)
{
    // Create the wide string
    std::wstring wstrWideString;

    // Copy the narrow string into the wide string from start to end
    wstrWideString.assign(strNarrowString.begin(), strNarrowString.end());

    return wstrWideString;
}

}
