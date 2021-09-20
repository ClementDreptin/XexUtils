#pragma once


namespace XexUtils
{

//--------------------------------------------------------------------------------------
// Name: class Formatter
// Desc: Utility static class to do string operations.
//--------------------------------------------------------------------------------------
class Formatter
{
public:
    static std::string Format(CONST std::string& strFormat, ...);
    static std::wstring ToWide(CONST std::string& strNarrowString);
};

}
