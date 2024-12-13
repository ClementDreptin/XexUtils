#include "pch.h"
#include "Log.h"

namespace XexUtils
{
namespace Log
{

static void Print(const char *format, const va_list args, std::ostream &outputStream)
{
    // Build the string with the format
    char buffer[2048] = {};
    vsnprintf_s(buffer, _TRUNCATE, format, args);

    // Print
    outputStream << buffer << '\n';
}

static void Print(const wchar_t *format, const va_list args, std::wostream &outputStream)
{
    // Build the string with the format
    wchar_t buffer[2048] = {};
    _vsnwprintf_s(buffer, _TRUNCATE, format, args);

    // Print
    outputStream << buffer << '\n';
}

void Info(const char *message, ...)
{
    // Get the variadic arguments
    va_list args;
    va_start(args, message);

    // Print
    std::string fullMessage = "Info: ";
    fullMessage += message;
    Print(fullMessage.c_str(), args, std::cout);

    // Free the variadic arguments
    va_end(args);
}

inline void Info(const std::string &message)
{
    Info(message.c_str());
}

void Info(const wchar_t *message, ...)
{
    // Get the variadic arguments
    va_list args;
    va_start(args, message);

    // Print
    std::wstring fullMessage = L"Info: ";
    fullMessage += message;
    Print(fullMessage.c_str(), args, std::wcout);

    // Free the variadic arguments
    va_end(args);
}

inline void Info(const std::wstring &message)
{
    Info(message.c_str());
}

void Error(const char *message, ...)
{
    // Get the variadic arguments
    va_list args;
    va_start(args, message);

    // Print
    std::string fullMessage = "Error: ";
    fullMessage += message;
    Print(fullMessage.c_str(), args, std::cerr);

    // Free the variadic arguments
    va_end(args);
}

inline void Error(const std::string &message)
{
    Error(message.c_str());
}

void Error(const wchar_t *message, ...)
{
    // Get the variadic arguments
    va_list args;
    va_start(args, message);

    // Print
    std::wstring fullMessage = L"Error: ";
    fullMessage += message;
    Print(fullMessage.c_str(), args, std::wcerr);

    // Free the variadic arguments
    va_end(args);
}

inline void Error(const std::wstring &message)
{
    Error(message.c_str());
}

}
}
