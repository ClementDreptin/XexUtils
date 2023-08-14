#include "pch.h"
#include "Log.h"

namespace XexUtils
{

void Log::Info(const char *message, ...)
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

void Log::Info(const wchar_t *message, ...)
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

void Log::Error(const char *message, ...)
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

void Log::Error(const wchar_t *message, ...)
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

void Log::Print(const char *format, const va_list args, std::ostream &outputStream)
{
    // Build the string with the format
    char buffer[2048] = { 0 };
    vsnprintf_s(buffer, _TRUNCATE, format, args);

    // Print
    outputStream << buffer << '\n';
}

void Log::Print(const wchar_t *format, const va_list args, std::wostream &outputStream)
{
    // Build the string with the format
    wchar_t buffer[2048] = { 0 };
    _vsnwprintf_s(buffer, _TRUNCATE, format, args);

    // Print
    outputStream << buffer << '\n';
}

}
