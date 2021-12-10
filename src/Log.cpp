#include "pch.h"
#include "Log.h"


namespace XexUtils
{

VOID Log::Info(CONST std::string &strMessage, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, strMessage);

    // Print
    Print("Info: " + strMessage, pArgList);

    // Free the variadic arguments
    va_end(pArgList);
}

VOID Log::Error(CONST std::string &strMessage, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, strMessage);

    // Print
    Print("Error: " + strMessage, pArgList);

    // Free the variadic arguments
    va_end(pArgList);
}

VOID Log::Print(CONST std::string &strFormat, CONST va_list pArgList)
{
    CONST INT MAX_SIZE = 2048;

    // Build the string with the format
    CHAR szBuffer[MAX_SIZE] = { 0 };
    vsnprintf_s(szBuffer, _TRUNCATE, strFormat.c_str(), pArgList);

    // Append \n to the string
    strcat_s(szBuffer, MAX_SIZE, "\n");

    // Print
    OutputDebugString(szBuffer);
}

}
