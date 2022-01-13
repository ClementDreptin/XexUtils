#include "pch.h"
#include "Log.h"


namespace XexUtils
{

void Log::Info(const std::string &strMessage, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, strMessage);

    // Print
    Print("Info: " + strMessage, pArgList);

    // Free the variadic arguments
    va_end(pArgList);
}

void Log::Error(const std::string &strMessage, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, strMessage);

    // Print
    Print("Error: " + strMessage, pArgList);

    // Free the variadic arguments
    va_end(pArgList);
}

void Log::Print(const std::string &strFormat, const va_list pArgList)
{
    const int MAX_SIZE = 2048;

    // Build the string with the format
    char szBuffer[MAX_SIZE] = { 0 };
    vsnprintf_s(szBuffer, _TRUNCATE, strFormat.c_str(), pArgList);

    // Append \n to the string
    strcat_s(szBuffer, MAX_SIZE, "\n");

    // Print
    OutputDebugString(szBuffer);
}

}
