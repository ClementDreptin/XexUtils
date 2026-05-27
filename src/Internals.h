#pragma once

// This file contains internal helpers that are not exposed by the public XexUtils.h
// header. That's why there's no Doxygen documentation.

namespace XexUtils
{

struct CaseInsensitiveHash
{
    size_t operator()(const std::string &key) const;
};

struct CaseInsensitiveEqual
{
    bool operator()(const std::string &lhs, const std::string &rhs) const;
};

std::string StringTrim(const std::string &str);

}
