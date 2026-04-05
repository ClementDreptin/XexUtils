#include "pch.h"
#include "Http.h"

#include "Formatter.h"

namespace XexUtils
{
namespace Http
{

const std::string Client::s_NewLineDelimiter = "\r\n";
const std::string Client::s_HeadersDelimiter = "\r\n\r\n";

Optional<Response> Client::Get(const std::string &domain, const std::string &path, bool secure, uint16_t port)
{
    Socket socket(domain, port, secure);
    HRESULT hr = socket.Connect();
    if (FAILED(hr))
        return NullOpt();

    std::stringstream requestStream;
    requestStream << "GET " << path << " HTTP/1.1\r\n";

    std::unordered_map<std::string, std::string> headers;
    headers["Host"] = domain;
    headers["User-Agent"] = "XexUtils HTTP client";
    headers["Accept"] = "*/*";
    headers["Connection"] = "close";

    for (auto it = headers.begin(); it != headers.end(); ++it)
    {
        const std::string &key = it->first;
        const std::string &value = it->second;
        requestStream << key << ": " << value << "\r\n";
    }
    requestStream << "\r\n";

    std::string request = requestStream.str();

    // Send it through the socket
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

    // Create the response
    Response response = {};

    Optional<uint32_t> status = ReadStatus(socket);
    if (!status)
        return NullOpt();

    response.Status = *status;
    response.Headers = ReadHeaders(socket);
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

std::unordered_map<std::string, std::string> Client::ReadHeaders(Socket &socket)
{
    std::unordered_map<std::string, std::string> headers;
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
