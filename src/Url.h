#pragma once

#include "Optional.h"

namespace XexUtils
{

typedef enum _UrlScheme
{
    UrlScheme_Https,
    UrlScheme_Http,
} UrlScheme;

class Url
{
public:
    static Optional<Url> Parse(const std::string &url);

    inline UrlScheme Scheme() const { return m_Scheme; }

    inline const std::string &Domain() const { return m_Domain; }

    inline const std::string &Path() const { return m_Path; }

    inline const std::string &Search() const { return m_Search; }

private:
    UrlScheme m_Scheme;
    std::string m_Domain;
    std::string m_Path;
    std::string m_Search;

    // Force Url objects to be created with the Parse function
    Url() {}
};

}
