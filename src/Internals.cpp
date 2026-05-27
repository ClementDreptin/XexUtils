#include "pch.h"
#include "Internals.h"

namespace XexUtils
{

size_t CaseInsensitiveHash::operator()(const std::string &key) const
{
    std::string lowercaseKey = key;
    std::transform(
        lowercaseKey.begin(),
        lowercaseKey.end(),
        lowercaseKey.begin(),
        [](unsigned char c) { return tolower(c); }
    );

    return std::hash<std::string>()(lowercaseKey);
}

bool CaseInsensitiveEqual::operator()(const std::string &lhs, const std::string &rhs) const
{
    if (lhs.size() != rhs.size())
        return false;

    for (size_t i = 0; i < lhs.size(); ++i)
        if (tolower(lhs[i]) != tolower(rhs[i]))
            return false;

    return true;
}

std::string StringTrim(const std::string &str)
{
    // Remove whitespaces at the beginning of the string
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return str;

    // Remove whitespaces at the end of the string
    size_t last = str.find_last_not_of(" \t\n\r");

    return str.substr(first, (last - first + 1));
}

}
