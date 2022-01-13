#pragma once


namespace XexUtils
{

// Utility static class with different printing functions.
class Log
{
public:
    // Print an info message to the console.
    static void Info(const std::string &strMessage, ...);

    // Print an error message to the console.
    static void Error(const std::string &strMessage, ...);
private:
    // Print a formatted message to the console.
    static void Print(const std::string &strFormat, const va_list pArgList);
};

}
