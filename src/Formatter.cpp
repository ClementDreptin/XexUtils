#include "pch.h"
#include "Formatter.h"

namespace XexUtils
{
namespace Formatter
{

std::string Format(const char *format, ...)
{
    XASSERT(format != nullptr);

    va_list args;
    va_start(args, format);

    char buffer[2048] = {};
    vsnprintf_s(buffer, _TRUNCATE, format, args);

    va_end(args);

    return std::string(buffer);
}

std::wstring Format(const wchar_t *format, ...)
{
    XASSERT(format != nullptr);

    va_list args;
    va_start(args, format);

    wchar_t buffer[2048] = {};
    _vsnwprintf_s(buffer, _TRUNCATE, format, args);

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
