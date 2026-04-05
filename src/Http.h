#pragma once

#include "Optional.h"
#include "Socket.h"

namespace XexUtils
{
namespace Http
{

struct Response
{
    uint32_t Status;
    std::unordered_map<std::string, std::string> Headers;
    std::string Body;
};

class Client
{
public:
    Optional<Response> Get(const std::string &domain, const std::string &path, bool secure = true, uint16_t port = 443);

private:
    std::vector<char> m_LeftoverData;

    Optional<uint32_t> ReadStatus(Socket &socket);

    std::unordered_map<std::string, std::string> ReadHeaders(Socket &socket);

    std::string ReadBody(Socket &socket);

private:
    static const std::string s_NewLineDelimiter;
    static const std::string s_HeadersDelimiter;
};

static std::string StringTrim(const std::string &str);

}

}
