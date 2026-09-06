#pragma once

// This module is heavily insipired by XboxTLS (https://github.com/JakobRangel/XboxTLS),
// which served as an example for integrating BearSSL on Xbox 360. Especially on how to
// provide a custom enthropy function using the native XeCrypt* functions.
//
// It is meant to be internal and only used by other XexUtils APIs, hence the lack of
// Doxygen documentation.

#include <bearssl.h>
#include <cstdint>
#include <string>
#include <vector>
#include <xtl.h>

namespace XexUtils
{

class TlsSession
{
public:
    TlsSession();

    void Start(const SOCKET &socket, const std::string &domain);

    void AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, int curveType);

    void AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize);

    int Send(const char *buffer, size_t size);

    int Receive(char *buffer, size_t maxSize);

private:
    br_ssl_client_context m_SslClientContext;
    br_x509_minimal_context m_x509Context;
    uint8_t m_IoBuffer[BR_SSL_BUFSIZE_BIDI];
    br_sslio_context m_IoContext;
    std::vector<br_x509_trust_anchor> m_TrustAnchors;

    static int SocketReadCallback(void *pContext, uint8_t *buffer, size_t maxSize);

    static int SocketWriteCallback(void *pContext, const uint8_t *buffer, size_t maxSize);
};

}
