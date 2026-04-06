#pragma once

#include "Optional.h"
#include "Socket.h"
#include "Url.h"

namespace XexUtils
{
namespace Http
{

struct Response;

class Client
{
public:
    void AddECTrustAnchor(const Socket::EllipticCurveTrustAnchor &trustAnchor);

    void AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, Socket::EllipticCurveType curveType);

    void AddRsaTrustAnchor(const Socket::RsaTrustAnchor &trustAnchor);

    void AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize);

    Optional<Response> Get(const std::string &domain, const std::string &path, bool secure = true, uint16_t port = 443);

private:
    std::vector<Socket::EllipticCurveTrustAnchor> m_ECTrustAnchors;
    std::vector<Socket::RsaTrustAnchor> m_RsaTrustAnchors;
    std::vector<char> m_LeftoverData;

    Optional<uint32_t> ReadStatus(Socket &socket);

    std::unordered_map<std::string, std::string> ReadHeaders(Socket &socket);

    std::string ReadBody(Socket &socket);
};

struct Response
{
    uint32_t Status;
    std::unordered_map<std::string, std::string> Headers;
    std::string Body;
};

static std::string StringTrim(const std::string &str);

}

}
