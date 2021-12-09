#pragma once


namespace XexUtils
{

// Utility static class with different printing functions.
class Log
{
public:
    // Print an info message to the console.
    static VOID Info(CONST std::string& strMessage, ...);

    // Print an error message to the console.
    static VOID Error(CONST std::string& strMessage, ...);
private:
    // Print a formatted message to the console.
    static VOID Print(CONST std::string& strFormat, CONST va_list pArgList);
};

}
