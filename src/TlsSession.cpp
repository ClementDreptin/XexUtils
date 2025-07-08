#include "pch.h"
#include "TlsSession.h"

#include <bearssl.h>

#include "Kernel.h"
#include "Memory.h"
#include "SystemSocket.h"

namespace XexUtils
{
namespace TlsSession
{

#define MAX_ANCHORS 100

static br_ssl_client_context s_SslClientContext = {};
static br_x509_minimal_context s_x509Context = {};
static uint8_t s_IoBuffer[BR_SSL_BUFSIZE_BIDI] = {};
static br_sslio_context s_IoContext = {};
static br_x509_trust_anchor s_TrustAnchors[MAX_ANCHORS] = {};
static size_t s_TrustAnchorCount = 0;
static br_hmac_drbg_context s_drbg = {};

static int SocketReadCallback(void *pContext, uint8_t *buffer, size_t maxSize)
{
    SOCKET socket = Memory::Read<SOCKET>(pContext);

    return recv(socket, reinterpret_cast<char *>(buffer), maxSize, 0);
}

static int SocketWriteCallback(void *pContext, const uint8_t *buffer, size_t maxSize)
{
    SOCKET socket = Memory::Read<SOCKET>(pContext);

    return send(socket, reinterpret_cast<const char *>(buffer), maxSize, 0);
}

HRESULT AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, EllipticCurveType curveType)
{
    XASSERT(dn != nullptr);
    XASSERT(q != nullptr);

    if (s_TrustAnchorCount == MAX_ANCHORS)
    {
        DebugPrint("[XexUtils][TlsSession]: Error: Max amount of trust anchors reached.");
        return E_FAIL;
    }

    s_TrustAnchors[s_TrustAnchorCount].dn.data = const_cast<uint8_t *>(dn);
    s_TrustAnchors[s_TrustAnchorCount].dn.len = dnSize;
    s_TrustAnchors[s_TrustAnchorCount].flags = BR_X509_TA_CA;
    s_TrustAnchors[s_TrustAnchorCount].pkey.key_type = BR_KEYTYPE_EC;
    s_TrustAnchors[s_TrustAnchorCount].pkey.key.ec.curve = curveType;
    s_TrustAnchors[s_TrustAnchorCount].pkey.key.ec.q = const_cast<uint8_t *>(q);
    s_TrustAnchors[s_TrustAnchorCount].pkey.key.ec.qlen = qSize;

    s_TrustAnchorCount++;

    return S_OK;
}

HRESULT AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize)
{
    XASSERT(dn != nullptr);
    XASSERT(n != nullptr);
    XASSERT(e != nullptr);

    if (s_TrustAnchorCount == MAX_ANCHORS)
    {
        DebugPrint("[XexUtils][TlsSession]: Error: Max amount of trust anchors reached.");
        return E_FAIL;
    }

    s_TrustAnchors[s_TrustAnchorCount].dn.data = const_cast<uint8_t *>(dn);
    s_TrustAnchors[s_TrustAnchorCount].dn.len = dnSize;
    s_TrustAnchors[s_TrustAnchorCount].flags = BR_X509_TA_CA;
    s_TrustAnchors[s_TrustAnchorCount].pkey.key_type = BR_KEYTYPE_EC;
    s_TrustAnchors[s_TrustAnchorCount].pkey.key.rsa.n = const_cast<uint8_t *>(n);
    s_TrustAnchors[s_TrustAnchorCount].pkey.key.rsa.nlen = nSize;
    s_TrustAnchors[s_TrustAnchorCount].pkey.key.rsa.e = const_cast<uint8_t *>(e);
    s_TrustAnchors[s_TrustAnchorCount].pkey.key.rsa.elen = eSize;

    s_TrustAnchorCount++;

    return S_OK;
}

void Start(const SOCKET &sock, const std::string &domain)
{
    XASSERT(sock != INVALID_SOCKET);
    XASSERT(domain.empty() == false);

    br_ssl_client_init_full(&s_SslClientContext, &s_x509Context, s_TrustAnchors, s_TrustAnchorCount);

    br_ssl_engine_set_buffer(&s_SslClientContext.eng, s_IoBuffer, sizeof(s_IoBuffer), 1);

    br_ssl_client_reset(&s_SslClientContext, domain.c_str(), 0);

    br_sslio_init(
        &s_IoContext,
        &s_SslClientContext.eng,
        SocketReadCallback,
        const_cast<SOCKET *>(&sock),
        SocketWriteCallback,
        const_cast<SOCKET *>(&sock)
    );
}

int Send(const char *buffer, size_t size)
{
    XASSERT(buffer != nullptr);

    if (br_sslio_write_all(&s_IoContext, buffer, size) != 0)
    {
        DebugPrint(
            "[XexUtils][TlsSession]: Error: SSL write error: %d",
            br_ssl_engine_last_error(&s_SslClientContext.eng)
        );
        return SOCKET_ERROR;
    }

    if (br_sslio_flush(&s_IoContext) != 0)
    {
        DebugPrint(
            "[XexUtils][TlsSession]: Error: SSL flush error: %d",
            br_ssl_engine_last_error(&s_SslClientContext.eng)
        );
        return SOCKET_ERROR;
    }

    return size;
}

int Receive(char *buffer, size_t maxSize)
{
    XASSERT(buffer != nullptr);

    int bytesRead = br_sslio_read(&s_IoContext, buffer, maxSize);

#ifndef NDEBUG
    int lastSslError = br_ssl_engine_last_error(&s_SslClientContext.eng);
    if (bytesRead < 0 && lastSslError != 0)
        DebugPrint("[XexUtils][Socket]: Error: SSL read error: %d", lastSslError);
#endif

    return bytesRead;
}

// Custom enthropy function
static int CustomSeeder(const br_prng_class **ppContext)
{
    uint8_t seed[32] = {};
    XeCryptRandom(seed, sizeof(seed));
    br_hmac_drbg_init(&s_drbg, &br_sha256_vtable, seed, sizeof(seed));
    *ppContext = s_drbg.vtable;

    return 1;
}

}
}

// Replace the original br_prng_seeder_system function from BearSSL with our own because the original
// one obviously doesn't support the Xbox 360
br_prng_seeder br_prng_seeder_system(const char **name)
{
    if (name)
        *name = "XeCryptRandom";

    return &XexUtils::TlsSession::CustomSeeder;
}
