#pragma once

// This module is heavily insipired by XboxTLS (https://github.com/JakobRangel/XboxTLS), which served as an example
// for integrating BearSSL on Xbox 360. Especially on how to provide a custom enthropy function using the native
// XeCrypt* functions.

namespace XexUtils
{
namespace TlsSession
{

// Elliptic curve identifiers used with EC trust anchors (aligned with BearSSL)
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

HRESULT AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, EllipticCurveType curveType);

HRESULT AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize);

void Start(const SOCKET &socket, const std::string &domain);

int Send(const char *buffer, size_t size);

int Receive(char *buffer, size_t maxSize);

}
}
