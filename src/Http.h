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

/// @brief A class to represent an HTTP client that sends requests and gets responses.
class Client
{
public:
    /// @brief Adds an Elliptic Curve trust anchor.
    /// @param trustAnchor The elliptic curve trust anchor info.
    void AddECTrustAnchor(const Socket::EllipticCurveTrustAnchor &trustAnchor);

    /// @brief Adds an Elliptic Curve trust anchor.
    /// @param dn The distinguished name.
    /// @param dnSize The amount of bytes in `dn`.
    /// @param q The public key curve point.
    /// @param qSize The amount of bytes in `q`.
    /// @param curveType The curve type.
    void AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, Socket::EllipticCurveType curveType);

    /// @brief Adds an RSA trust anchor.
    /// @param trustAnchor The RSA trust anchor info.
    void AddRsaTrustAnchor(const Socket::RsaTrustAnchor &trustAnchor);

    /// @brief Adds an RSA trust anchor.
    /// @param dn The distinguished name.
    /// @param dnSize The amount of bytes in `dn`.
    /// @param n The public key modulus.
    /// @param nSize The amount of bytes in `n`.
    /// @param e The public key exponent.
    /// @param eSize The amount of bytes in `e`.
    void AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize);

    /// @brief Sends a GET request to `url`.
    ///
    /// This function can fail if `url` is invalid, if connecting to the server fails,
    /// if sending the request fails, if reading the response fails, or if following the
    /// potential redirects fails.
    ///
    /// @param url The URL.
    /// @return A valid `Optional<Response>` on success, and empty `Optional` on error.
    Optional<Response> Get(const std::string &url);

    /// @brief Sends a POST request to `url`.
    ///
    /// This function can fail if `url` is invalid, if connecting to the server fails,
    /// if sending the request fails, if reading the response fails, or if following the
    /// potential redirects fails.
    ///
    /// @param url The URL.
    /// @param body The request body.
    /// @return A valid `Optional<Response>` on success, and empty `Optional` on error.
    Optional<Response> Post(const std::string &url, const std::string &body);

    /// @brief Sends a request.
    ///
    /// This function can fail if connecting to the server fails, if sending the request
    /// fails, if reading the response fails, or if following the potential redirects fails.
    ///
    /// @param options The request options.
    /// @return A valid `Optional<Response>` on success, and empty `Optional` on error.
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

/// @brief An enum to represent the supported HTTP methods (GET and POST).
typedef enum _Method
{
    Method_Get,
    Method_Post,
} Method;

/// @brief A struct to represent the request options.
struct RequestOptions
{
    /// @brief Creates a `RequestOptions` from a `Url`.
    /// @param url The `Url` instance.
    RequestOptions(const Url &url);

    /// @brief The parsed URL.
    Url Url;

    /// @brief The method (see `Method` enum).
    Method Method;

    /// @brief The headers as an `std::unordered_map<std::string, std::string>`.
    Headers Headers;

    /// @brief The request body.
    std::string Body;
};

/// @brief A struct to represent a response.
struct Response
{
    /// @brief Converts the binary body into an `std::string`.
    /// @return An `std::string` from the binary body.
    std::string BodyAsString() const;

    /// @brief The status code.
    uint32_t Status;

    /// @brief The headers as an `std::unordered_map<std::string, std::string>`.
    Headers Headers;

    /// @brief The response body as a vector of bytes.
    std::vector<uint8_t> Body;
};

}

}
