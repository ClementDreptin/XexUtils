#include "pch.h"
#include "Log.h"

namespace XexUtils
{

static const int MAX_SIZE = 2048;

void Log::Info(const char *szMessage, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, szMessage);

    // Print
    std::string strFullMessage = "Info: ";
    strFullMessage += szMessage;
    Print(strFullMessage.c_str(), pArgList, std::cout);

    // Free the variadic arguments
    va_end(pArgList);
}

void Log::Error(const char *szMessage, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, szMessage);

    // Print
    std::string strFullMessage = "Error: ";
    strFullMessage += szMessage;
    Print(strFullMessage.c_str(), pArgList, std::cerr);

    // Free the variadic arguments
    va_end(pArgList);
}

void Log::Print(const char *szFormat, const va_list pArgList, std::ostream &OutputStream)
{
    // Build the string with the format
    char szBuffer[MAX_SIZE] = { 0 };
    vsnprintf_s(szBuffer, _TRUNCATE, szFormat, pArgList);

    // Print
    OutputStream << szBuffer << '\n';
}

}
