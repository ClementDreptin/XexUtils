#pragma once


namespace XexUtils
{

//--------------------------------------------------------------------------------------
// Name: class Log
// Desc: Utility static class with different printing functions.
//--------------------------------------------------------------------------------------
class Log
{
public:
    static VOID Info(CONST std::string& strMessage, ...);
    static VOID Error(CONST std::string& strMessage, ...);
private:
    static VOID Print(CONST std::string& strFormat, CONST va_list pArgList);
};

}
