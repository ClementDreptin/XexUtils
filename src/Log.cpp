#include "pch.h"
#include "Log.h"

namespace XexUtils
{
namespace Log
{

void Print(const char *format, ...)
{
    XASSERT(format != nullptr);

    va_list args;
    va_start(args, format);

    char buffer[2048] = {};
    vsnprintf_s(buffer, _TRUNCATE, format, args);

    std::cout << buffer << '\n';

    va_end(args);
}

void Print(const std::string &message)
{
    std::cout << message << '\n';
}

void Print(const wchar_t *format, ...)
{
    XASSERT(format != nullptr);

    va_list args;
    va_start(args, format);

    wchar_t buffer[2048] = {};
    _vsnwprintf_s(buffer, _TRUNCATE, format, args);

    std::wcout << buffer << '\n';

    va_end(args);
}

void Print(const std::wstring &message)
{
    std::wcout << message << '\n';
}

}
}
