#pragma once

namespace XexUtils
{

// Utility static class with different printing functions.
class Log
{
public:
    // Print an info message to stdout.
    static void Info(const char *message, ...);

    // Print an info message to stdout.
    inline static void Info(const std::string &message) { Info(message.c_str()); }

    // Print an error message to stderr.
    static void Error(const char *message, ...);

    // Print an error message to stderr.
    inline static void Error(const std::string &message) { Error(message.c_str()); }

private:
    // Print a formatted message to an output stream.
    static void Print(const char *format, const va_list args, std::ostream &outputStream);
};

}
