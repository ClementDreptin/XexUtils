#include "pch.h"
#include "Http.h"

#include "Formatter.h"

namespace XexUtils
{
namespace Http
{

static const std::string s_NewLineDelimiter = "\r\n";
static const std::string s_HeadersDelimiter = "\r\n\r\n";

void Client::AddECTrustAnchor(const Socket::EllipticCurveTrustAnchor &trustAnchor)
{
    m_ECTrustAnchors.emplace_back(trustAnchor);
}

void Client::AddECTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *q, size_t qSize, Socket::EllipticCurveType curveType)
{
    Socket::EllipticCurveTrustAnchor trustAnchor;
    trustAnchor.DN = std::vector<uint8_t>(dn, dn + dnSize);
    trustAnchor.Q = std::vector<uint8_t>(q, q + qSize);
    trustAnchor.Type = curveType;
    m_ECTrustAnchors.emplace_back(trustAnchor);
}

void Client::AddRsaTrustAnchor(const Socket::RsaTrustAnchor &trustAnchor)
{
    m_RsaTrustAnchors.emplace_back(trustAnchor);
}

void Client::AddRsaTrustAnchor(const uint8_t *dn, size_t dnSize, const uint8_t *n, size_t nSize, const uint8_t *e, size_t eSize)
{
    Socket::RsaTrustAnchor trustAnchor;
    trustAnchor.DN = std::vector<uint8_t>(dn, dn + dnSize);
    trustAnchor.N = std::vector<uint8_t>(n, n + nSize);
    trustAnchor.E = std::vector<uint8_t>(e, e + eSize);
    m_RsaTrustAnchors.emplace_back(trustAnchor);
}

Optional<Response> Client::Get(const std::string &url)
{
    Optional<Url> parsedUrl = Url::Parse(url);
    if (!parsedUrl)
        return NullOpt();

    return Get(*parsedUrl);
}

Optional<Response> Client::Get(const Url &url)
{
    RequestOptions options(url);
    options.Method = Method_Get;

    return SendRequest(options);
}

Optional<Response> Client::Post(const std::string &url, const std::string &body)
{
    Optional<Url> parsedUrl = Url::Parse(url);
    if (!parsedUrl)
        return NullOpt();

    RequestOptions options(*parsedUrl);
    options.Method = Method_Post;
    options.Body = body;
    options.Headers["Content-Type"] = "text/plain";
    options.Headers["Content-Length"] = std::to_string(static_cast<uint64_t>(body.size()));

    return SendRequest(options);
}

Optional<Response> Client::SendRequest(const RequestOptions &options)
{
    bool secure = options.Url.Scheme() == UrlScheme_Https;

    // Create the socket
    Socket socket(options.Url.Domain(), options.Url.Port(), secure);

    // Add the registered trust anchors to the socket when in secure mode
    if (secure)
    {
        XASSERT(!m_ECTrustAnchors.empty() || !m_RsaTrustAnchors.empty())

        for (size_t i = 0; i < m_ECTrustAnchors.size(); i++)
            socket.AddECTrustAnchor(m_ECTrustAnchors[i]);

        for (size_t i = 0; i < m_RsaTrustAnchors.size(); i++)
            socket.AddRsaTrustAnchor(m_RsaTrustAnchors[i]);
    }

    // Connect to the server
    HRESULT hr = socket.Connect();
    if (FAILED(hr))
        return NullOpt();

    // Create the request string
    std::stringstream requestStream;

    // Convert the method enum to a string
    const char *methodString = MethodToString(options.Method);
#ifndef NDEBUG
    if (methodString == nullptr)
    {
        DebugPrint(
            "[XexUtils][Http]: Error: Incorrect HTTP method \"%d\" (see Http::Method enum).",
            options.Method
        );
        return NullOpt();
    }
#endif

    // Create the first line with the method and the resource path
    requestStream << methodString << " " << options.Url.Path() << " HTTP/1.1\r\n";

    // Create the headers
    Headers finalHeaders = CreateFinalHeaders(options.Headers, options.Url.Domain());
    for (auto it = finalHeaders.begin(); it != finalHeaders.end(); ++it)
    {
        const std::string &key = it->first;
        const std::string &value = it->second;
        requestStream << key << ": " << value << "\r\n";
    }
    requestStream << "\r\n";

    // Append the body to the request
    requestStream << options.Body;

    std::string request = requestStream.str();

    // Send the request through the socket
    int bytesSent = socket.Send(request.c_str(), request.size());
    if (bytesSent < static_cast<int>(request.size()))
    {
        DebugPrint(
            "[XexUtils][Http]: Error: Not all bytes could be sent, expected to send %d but only sent %d.",
            request.size(),
            bytesSent
        );
        return NullOpt();
    }

    // Read the status
    Optional<uint32_t> status = ReadStatus(socket);
    if (!status)
        return NullOpt();

    // Read the headers
    Headers headers = ReadHeaders(socket);

    // If the response is a redirect, follow the redirect
    if (*status >= 300 && *status < 400)
    {
        if (headers.find("Location") == headers.end())
        {
            DebugPrint(
                "[XexUtils][Http]: Error: Tried to follow a redirect (%d) but the "
                "\"Location\" header is missing.",
                *status
            );
            return NullOpt();
        }

        Optional<Url> newLocation = Url::Parse(headers["Location"]);
        if (!newLocation)
        {
            DebugPrint(
                "[XexUtils][Http]: Error: Couldn't follow a redirect (%d) because the "
                "\"Location\" header (%s) is not a valid URL.",
                *status,
                headers["Location"].c_str()
            );
            return NullOpt();
        }

        RequestOptions newOptions(*newLocation);
        newOptions.Method = options.Method;
        newOptions.Headers = finalHeaders;
        newOptions.Body = options.Body;

        return SendRequest(newOptions);
    }

    // Create the response
    Response response = {};
    response.Status = *status;
    response.Headers = headers;
    response.Body = ReadBody(socket);

    return response;
}

Optional<uint32_t> Client::ReadStatus(Socket &socket)
{
    // Clear any previous leftover data
    m_LeftoverData.clear();

    // Read from the socket
    char buffer[64] = {};
    int bytesRead = socket.Receive(buffer, sizeof(buffer) - 1);
    if (bytesRead <= 0)
    {
        DebugPrint("[Hayzen][Http]: Error: Couldn't read status line.");
        return NullOpt();
    }

    std::string data(buffer, bytesRead);

    // If the new line delimiter hasn't been read, just push what was read into the
    // leftover data and stop
    size_t newLinePos = data.find(s_NewLineDelimiter);
    if (newLinePos == std::string::npos)
    {
        m_LeftoverData.insert(m_LeftoverData.end(), data.begin(), data.end());
        return NullOpt();
    }

    // Separate the status line from the rest and push the rest into the leftover data
    std::string statusLine = data.substr(0, newLinePos);
    m_LeftoverData.insert(
        m_LeftoverData.end(),
        data.begin() + newLinePos + s_NewLineDelimiter.size(),
        data.end()
    );

    // Extract status code from status line
    uint32_t status = 0;
    if (sscanf_s(statusLine.c_str(), "HTTP/1.1 %d", &status) != 1)
    {
        DebugPrint(
            "[XexUtils][Http]: Error: Couldn't extract status code from \"%s\"",
            statusLine.c_str()
        );
        return NullOpt();
    }

    return status;
}

Headers Client::ReadHeaders(Socket &socket)
{
    Headers headers;
    std::stringstream headerStream;
    char buffer[2048] = {};
    bool headersComplete = false;

    // If any leftover data is present from previous reads, use them before reading from
    // the socket
    if (!m_LeftoverData.empty())
    {
        headerStream.write(m_LeftoverData.data(), m_LeftoverData.size());
        m_LeftoverData.clear();
    }

    // Read until all headers are read
    while (!headersComplete)
    {
        int bytesRead = socket.Receive(buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0)
            break;

        std::string chunk(buffer, bytesRead);

        // If the end of the headers hasn't been reached yet, just push the chunk into the
        // global stream and continue
        size_t headersEndPos = chunk.find(s_HeadersDelimiter);
        if (headersEndPos == std::string::npos)
        {
            headerStream << chunk;
            continue;
        }

        // Push the chunk into the global stream up to the end of the headers
        headerStream << chunk.substr(0, headersEndPos);

        // If the chunk contains data after the end of the headers, push it into the global
        // leftover buffer
        m_LeftoverData.insert(
            m_LeftoverData.end(),
            chunk.begin() + headersEndPos + s_HeadersDelimiter.size(),
            chunk.end()
        );

        headersComplete = true;
    }

    // Read the headers line by line and create the map
    std::string headerLine;
    while (std::getline(headerStream, headerLine, '\n'))
    {
        headerLine = StringTrim(headerLine);
        size_t colonPos = headerLine.find(':');

        // If the header doesn't contain a ":", then it's malformed, so just skip it
        if (colonPos == std::string::npos)
            continue;

        std::string key = StringTrim(headerLine.substr(0, colonPos));
        std::string value = StringTrim(headerLine.substr(colonPos + 1));
        headers[key] = value;
    }

    return headers;
}

std::string Client::ReadBody(Socket &socket)
{
    std::stringstream bodyStream;
    char buffer[2048] = {};

    // If any leftover data is present from previous reads, use them before reading from
    // the socket
    if (!m_LeftoverData.empty())
    {
        bodyStream.write(m_LeftoverData.data(), m_LeftoverData.size());
        m_LeftoverData.clear();
    }

    // Flush the socket
    for (;;)
    {
        int bytesRead = socket.Receive(buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0)
            break;

        buffer[bytesRead] = '\0';
        bodyStream << buffer;
    }

    return bodyStream.str();
}

Headers Client::CreateFinalHeaders(const Headers &baseHeaders, const std::string &domain)
{
    XASSERT(!domain.empty());

    Headers finalHeaders = baseHeaders;

    // The host header is always the domain, it can't be overridden
    finalHeaders["Host"] = domain;

    // Set some headers if they're not already present
    if (finalHeaders.find("User-Agent") == finalHeaders.end())
        finalHeaders["User-Agent"] = "XexUtils HTTP client";

    if (finalHeaders.find("Accept") == finalHeaders.end())
        finalHeaders["Accept"] = "*/*";

    // This header is forced because keep-alive isn't supported
    finalHeaders["Connection"] = "close";

    return finalHeaders;
}

RequestOptions::RequestOptions(const XexUtils::Url &url)
    : Url(url)
{
}

const char *MethodToString(Method method)
{
    switch (method)
    {
    case Method_Get:
        return "GET";
    case Method_Post:
        return "POST";
    default:
        return nullptr;
    }
}

std::string StringTrim(const std::string &str)
{
    // Remove whitespaces at the beginning of the string
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return str;

    // Remove whitespaces at the end of the string
    size_t last = str.find_last_not_of(" \t\n\r");

    return str.substr(first, (last - first + 1));
}

}
}
