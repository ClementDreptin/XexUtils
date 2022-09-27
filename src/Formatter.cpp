#include "pch.h"
#include "Formatter.h"

namespace XexUtils
{

std::string Formatter::Format(const char *format, ...)
{
    // Get the variadic arguments
    va_list args;
    va_start(args, format);

    // Build the string with the format
    char buffer[2048] = { 0 };
    vsnprintf_s(buffer, _TRUNCATE, format, args);

    // Free the variadic arguments
    va_end(args);

    return std::string(buffer);
}

std::wstring Formatter::ToWide(const std::string &narrowString)
{
    // Create the wide string
    std::wstring wideString;

    // Copy the narrow string into the wide string from start to end
    wideString.assign(narrowString.begin(), narrowString.end());

    return wideString;
}

}
