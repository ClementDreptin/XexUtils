#pragma once

/// @file TlsSession.h
///
/// This module is heavily insipired by XboxTLS (https://github.com/JakobRangel/XboxTLS),
/// which served as an example for integrating BearSSL on Xbox 360. Especially on how to
/// provide a custom enthropy function using the native XeCrypt* functions.
///
/// It is meant to be internal and only used by other XexUtils APIs.

namespace XexUtils
{
namespace TlsSession
{

/// @brief Elliptic curve identifiers used with EC trust anchors (aligned with BearSSL).
typedef enum
{
    Curve_sect163k1 = 1,
    Curve_sect163r1,
    Curve_sect163r2,
    Curve_sect193r1,
    Curve_sect193r2,
    Curve_sect233k1,
    Curve_sect233r1,
    Curve_sect239k1,
    Curve_sect283k1,
    Curve_sect283r1,
    Curve_sect409k1,
    Curve_sect409r1,
    Curve_sect571k1,
    Curve_sect571r1,
    Curve_secp160k1,
    Curve_secp160r1,
    Curve_secp160r2,
    Curve_secp192k1,
    Curve_secp192r1,
    Curve_secp224k1,
    Curve_secp224r1,
    Curve_secp256k1,
    Curve_secp256r1,
    Curve_secp384r1,
    Curve_secp521r1,
    Curve_brainpoolP256r1,
    Curve_brainpoolP384r1,
    Curve_brainpoolP512r1,
    Curve_curve25519,
    Curve_curve448
} EllipticCurveType;

/// @brief Adds an Elliptic Curve trust anchor.
///
/// This function can fail if the total amount of trust anchors exceeds `MAX_ANCHORS`.
///
/// @param dn The distinguished name.
/// @param dnSize The amount of bytes in `dn`.
/// @param q The public key curve point.
/// @param qSize The amount of bytes in `q`.
/// @param curveType The curve type.
/// @return `S_OK` on success, `E_FAIL` on error.
HRESULT AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, EllipticCurveType curveType);

/// @brief Adds an RSA trust anchor.
///
/// This function can fail if the total amount of trust anchors exceeds `MAX_ANCHORS`.
///
/// @param dn The distinguished name.
/// @param dnSize The amount of bytes in `dn`.
/// @param n The public key modulus.
/// @param nSize The amount of bytes in `n`.
/// @param e The public key exponent.
/// @param eSize The amount of bytes in `e`.
/// @return `S_OK` on success, `E_FAIL` on error.
HRESULT AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize);

/// @brief Initializes a TLS session.
/// @param socket The socket to start the session on.
/// @param domain The domain name to verify the certificates against.
void Start(const SOCKET &socket, const std::string &domain);

/// @brief Sends `size` bytes from `buffer` into the socket associated with the TLS session.
///
/// This function can fail if not all bytes could be sent.
///
/// @param buffer The buffer to send data from.
/// @param size The amount of bytes to send.
/// @return The amount of bytes sent on success, `SOCKET_ERROR` on error.
int Send(const char *buffer, size_t size);

/// @brief Receives at most `maxSize` bytes from the socket associated with the TLS
/// session and store them in `buffer`.
/// @param buffer The buffer to store data into.
/// @param maxSize The max amount of bytes to receive.
/// @return The amount of bytes sent on success, `SOCKET_ERROR` on error or when no bytes
/// were received.
int Receive(char *buffer, size_t maxSize);

}
}
