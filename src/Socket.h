#pragma once

#include "TlsSession.h"

namespace XexUtils
{

class Socket
{
public:
    Socket();
    Socket(const std::string &domain, uint16_t port, bool secure = true);
    Socket(const Socket &other);
    ~Socket();

    HRESULT Connect();

    void Disconnect();

    int Send(const char *buffer, size_t size);

    int Receive(char *buffer, size_t maxSize);

    HRESULT AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, TlsSession::EllipticCurveType curveType);

    HRESULT AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize);

private:
    SOCKET m_Socket;
    std::string m_Domain;
    uint16_t m_Port;
    bool m_Secure;

    bool m_Connected;

    IN_ADDR DnsLookup();

    void InitInternal(const std::string &domain, uint16_t port, bool secure);

private:
    static bool s_Initialized;
    static size_t s_ReferenceCounter;

    static HRESULT Init();

    static void Cleanup();
};

}
