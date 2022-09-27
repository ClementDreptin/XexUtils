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

void Log::Print(const char *format, const va_list args, std::ostream &outputStream)
{
    // Build the string with the format
    char buffer[2048] = { 0 };
    vsnprintf_s(buffer, _TRUNCATE, format, args);

    // Print
    outputStream << buffer << '\n';
}

}
