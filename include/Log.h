#pragma once


namespace XexUtils
{

// Utility static class with different printing functions.
class Log
{
public:
    // Print an info message to stdout.
    static void Info(const char *szMessage, ...);

    // Print an error message to stderr.
    static void Error(const char *szMessage, ...);
private:
    // Print a formatted message to an output stream.
    static void Print(const char *szFormat, const va_list pArgList, std::ostream &OutputStream);
};

}
