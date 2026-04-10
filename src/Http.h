#pragma once

#include "Optional.h"
#include "Socket.h"
#include "Url.h"

namespace XexUtils
{
namespace Http
{

typedef std::unordered_map<std::string, std::string> Headers;

struct RequestOptions;
struct Response;

class Client
{
public:
    void AddECTrustAnchor(const Socket::EllipticCurveTrustAnchor &trustAnchor);

    void AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, Socket::EllipticCurveType curveType);

    void AddRsaTrustAnchor(const Socket::RsaTrustAnchor &trustAnchor);

    void AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize);

    Optional<Response> Get(const std::string &url);

    Optional<Response> Post(const std::string &url, const std::string &body);

    Optional<Response> SendRequest(const RequestOptions &options);

private:
    std::vector<Socket::EllipticCurveTrustAnchor> m_ECTrustAnchors;
    std::vector<Socket::RsaTrustAnchor> m_RsaTrustAnchors;
    std::vector<char> m_LeftoverData;

    Optional<uint32_t> ReadStatus(Socket &socket);

    Headers ReadHeaders(Socket &socket);

    std::vector<uint8_t> ReadBody(Socket &socket, size_t contentLength);

    Headers CreateFinalHeaders(const Headers &baseHeaders, const RequestOptions &options);
};

typedef enum _Method
{
    Method_Get,
    Method_Post,
} Method;

struct RequestOptions
{
    RequestOptions(const Url &url);

    Url Url;
    Method Method;
    Headers Headers;
    std::string Body;
};

struct Response
{
    std::string BodyAsString() const;

    uint32_t Status;
    Headers Headers;
    std::vector<uint8_t> Body;
};

static const char *MethodToString(Method method);

static std::string StringTrim(const std::string &str);

}

}
