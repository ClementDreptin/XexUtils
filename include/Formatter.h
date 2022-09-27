#pragma once

namespace XexUtils
{

// Utility static class to do string operations.
class Formatter
{
public:
    // Format a string in with a printf-like format.
    static std::string Format(const char *format, ...);

    // Create a wide string from a narrow string.
    static std::wstring ToWide(const std::string &narrowString);
};

}
