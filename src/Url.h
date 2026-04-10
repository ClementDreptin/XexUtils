#pragma once

#include "Optional.h"

namespace XexUtils
{

/// @brief An enum to represent HTTP URL schemes (HTTP or HTTPS).
typedef enum _UrlScheme
{
    UrlScheme_Https,
    UrlScheme_Http,
} UrlScheme;

/// @brief A class to represent a parsed URL.
class Url
{
public:
    /// @brief Creates an `Url` from an `std::string`.
    ///
    /// This function can fail if `url` isn't a valid URL.
    ///
    /// @param url The URL.
    /// @return A valid `Optional<Url>` on success, and empty `Optional` on error.
    static Optional<Url> Parse(const std::string &url);

    /// @brief Gets the scheme component of the `Url`.
    /// @return The scheme.
    inline UrlScheme Scheme() const { return m_Scheme; }

    /// @brief Gets the domain component of the `Url`.
    /// @return The domain.
    inline const std::string &Domain() const { return m_Domain; }

    /// @brief Gets the port component of the `Url`.
    /// @return The port.
    inline uint16_t Port() const { return m_Port; }

    /// @brief Gets the path component of the `Url`.
    /// @return The path.
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
