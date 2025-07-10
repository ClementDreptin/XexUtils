#pragma once

#include "TlsSession.h"

namespace XexUtils
{

/// @brief A class representing a socket connection.
class Socket
{
public:
    /// @brief Creates an empty `Socket`.
    Socket();

    /// @brief Creates a `Socket`.
    /// @param domain The domain name to connect to.
    /// @param port The port to connect to.
    /// @param secure Wether to use TLS or not.
    Socket(const std::string &domain, uint16_t port, bool secure = true);

    /// @brief Creates a copy from an existing `Socket`.
    /// @param other The other `Socket` to copy from.
    Socket(const Socket &other);

    /// @brief Calls `Disconnect`.
    ~Socket();

    /// @brief Connects the socket to the specified domain and port.
    ///
    /// The built-in encryption, which is different from TLS, is disabled. It means the
    /// running process needs to have the insecure socket privilege.
    ///
    /// This function can fail if the DNS lookup fails (invalid name, DNS server
    /// connectivity issues), if disabling the built-in encryption fails (insufficient
    /// privilege), or if the server doesn't listen on the specified port.
    ///
    /// @return `S_OK` on success, `E_FAIL` on error.
    HRESULT Connect();

    /// @brief Shuts down and closes the socket.
    void Disconnect();

    /// @brief Sends `size` bytes from `buffer` into the socket connection.
    ///
    /// When TLS is enabled, exactly `size` bytes need to be sent for the function to
    /// succeed. When TLS is disabled, this function just calls `send` from the standard
    /// library.
    ///
    /// @param buffer The buffer to send data from.
    /// @param size The amount of bytes to send.
    /// @return The amount of bytes sent on success, `SOCKET_ERROR` on error.
    int Send(const char *buffer, size_t size);

    /// @brief Receives at most `maxSize` bytes from the socket connection and store them
    /// in `buffer`.
    ///
    /// When TLS is disabled, this function just calls `recv` from the standard library.
    ///
    /// @param buffer The buffer to store data into.
    /// @param maxSize The max amount of bytes to receive.
    /// @return The amount of bytes sent on success, `SOCKET_ERROR` on error or when no
    /// bytes were received.
    int Receive(char *buffer, size_t maxSize);

    /// @brief Adds an Elliptic Curve trust anchor.
    ///
    /// This function can fail if TLS is disabled or if the total amount of trust anchors
    /// exceeds `MAX_ANCHORS`.
    ///
    /// @param dn The distinguished name.
    /// @param dnSize The amount of bytes in `dn`.
    /// @param q The public key curve point.
    /// @param qSize The amount of bytes in `q`.
    /// @param curveType The curve type.
    /// @return `S_OK` on success, `E_FAIL` on error.
    HRESULT AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, TlsSession::EllipticCurveType curveType);

    /// @brief Adds an RSA trust anchor.
    ///
    /// This function can fail if TLS is disabled or if the total amount of trust anchors
    /// exceeds `MAX_ANCHORS`.
    ///
    /// @param dn The distinguished name.
    /// @param dnSize The amount of bytes in `dn`.
    /// @param n The public key modulus.
    /// @param nSize The amount of bytes in `n`.
    /// @param e The public key exponent.
    /// @param eSize The amount of bytes in `e`.
    /// @return `S_OK` on success, `E_FAIL` on error.
    HRESULT AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize);

private:
    SOCKET m_Socket;
    std::string m_Domain;
    uint16_t m_Port;
    bool m_Secure;

    bool m_Connected;

    IN_ADDR DnsLookup();

private:
    static bool s_Initialized;
    static size_t s_ReferenceCounter;

    static HRESULT GlobalInit();

    static void GlobalCleanup();
};

}
