#include "pch.h"
#include "Log.h"


static CONST INT MAX_SIZE = 2048;

namespace XexUtils
{
namespace Log
{
    // Forward declaration for the main printing function
    static VOID Print(const std::string& strFormat, const va_list pArgList);

    //--------------------------------------------------------------------------------------
    // Name: Info()
    // Desc: Print an info message to the console.
    //--------------------------------------------------------------------------------------
    VOID Info(const std::string& strMessage, ...)
    {
        // Get the variadic arguments
        va_list pArgList;
        va_start(pArgList, strMessage);

        // Print
        Print("Info: " + strMessage, pArgList);

        // Free the variadic arguments
        va_end(pArgList);
    }


    //--------------------------------------------------------------------------------------
    // Name: Error()
    // Desc: Print an error message to the console.
    //--------------------------------------------------------------------------------------
    VOID Error(const std::string& strMessage, ...)
    {
        // Get the variadic arguments
        va_list pArgList;
        va_start(pArgList, strMessage);

        // Print
        Print("Error: " + strMessage, pArgList);

        // Free the variadic arguments
        va_end(pArgList);
    }


    //--------------------------------------------------------------------------------------
    // Name: Print()
    // Desc: Print a formatted message to the console.
    //--------------------------------------------------------------------------------------
    static VOID Print(const std::string& strFormat, const va_list pArgList)
    {
        // Build the string with the format
        CHAR szBuffer[MAX_SIZE] = { 0 };
        vsnprintf_s(szBuffer, _TRUNCATE, strFormat.c_str(), pArgList);

        // Append \n to the string
        strcat_s(szBuffer, MAX_SIZE, "\n");

        // Print
        OutputDebugString(szBuffer);
    }

}
}
