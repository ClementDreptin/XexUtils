#pragma once


namespace XexUtils
{

// Utility static class to do string operations.
class Formatter
{
public:
    // Format a string in with a printf-like format.
    static std::string Format(CONST std::string& strFormat, ...);

    // Create a wide string from a narrow string.
    static std::wstring ToWide(CONST std::string& strNarrowString);
};

}
