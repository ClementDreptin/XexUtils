#pragma once

namespace XexUtils
{

class Formatter
{
public:
    static std::string Format(const char *format, ...);

    static std::wstring ToWide(const std::string &narrowString);

    static std::string ToNarrow(const std::wstring &wideString);
};

}
