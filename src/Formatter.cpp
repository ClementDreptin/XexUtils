#include "pch.h"
#include "Formatter.h"

namespace XexUtils
{
namespace Formatter
{

std::string Format(const char *format, ...)
{
    // Get the variadic arguments
    va_list args;
    va_start(args, format);

    // Build the string with the format
    char buffer[2048] = {};
    vsnprintf_s(buffer, _TRUNCATE, format, args);

    // Free the variadic arguments
    va_end(args);

    return std::string(buffer);
}

std::wstring WideFormat(const wchar_t *format, ...)
{
    // Get the variadic arguments
    va_list args;
    va_start(args, format);

    // Build the string with the format
    wchar_t buffer[2048] = {};
    _vsnwprintf_s(buffer, _TRUNCATE, format, args);

    // Free the variadic arguments
    va_end(args);

    return std::wstring(buffer);
}

std::wstring ToWide(const std::string &narrowString)
{
    return std::wstring(narrowString.begin(), narrowString.end());
}

std::string ToNarrow(const std::wstring &wideString)
{
    return std::string(wideString.begin(), wideString.end());
}

}
}
