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

    inline uint16_t Port() const { return m_Port; }

    inline const std::string &Path() const { return m_Path; }

private:
    UrlScheme m_Scheme;
    std::string m_Domain;
    uint16_t m_Port;
    std::string m_Path;

    // Make the constructor private to force Url objects to be created with the Parse function
    Url() {}
};

}
