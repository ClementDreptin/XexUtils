#include "pch.h"
#include "Url.h"

namespace XexUtils
{

static const std::string s_ProtocolDelimiter = "://";

Optional<Url> Url::Parse(const std::string &url)
{
    Url parsedUrl;

    // Find the end of the protocol
    size_t protocolEndPos = url.find(s_ProtocolDelimiter);
    if (protocolEndPos == std::string::npos)
    {
        DebugPrint(
            "[XexUtils][Http]: Error: \"%s\" is not a valid URL. It doesn't contain a protocol.",
            url.c_str()
        );
        return NullOpt();
    }

    // Make sure the protocol is either "https" or "http"
    std::string protocol = url.substr(0, protocolEndPos);
    if (protocol == "https")
    {
        parsedUrl.m_Scheme = UrlScheme_Https;
    }
    else if (protocol == "http")
    {
        parsedUrl.m_Scheme = UrlScheme_Http;
    }
    else
    {
        DebugPrint(
            "[XexUtils][Http]: Error: \"%s\" is not a valid URL. Unknown protocol: \"%s\".",
            url.c_str(),
            protocol.c_str()
        );
        return NullOpt();
    }

    // If the URL ends after the protocol, so the domain is empty, it's invalid
    size_t domainStartPos = protocolEndPos + s_ProtocolDelimiter.size();
    if (domainStartPos == url.size())
    {
        DebugPrint(
            "[XexUtils][Http]: Error: \"%s\" is not a valid URL. It doesn't contain a domain.",
            url.c_str()
        );
        return NullOpt();
    }

    // Extract the domain
    size_t pathStartPos = url.find('/', domainStartPos);
    parsedUrl.m_Domain =
        pathStartPos != std::string::npos
            ? url.substr(domainStartPos, pathStartPos - domainStartPos)
            : url.substr(domainStartPos);

    // Extract the path
    parsedUrl.m_Path = pathStartPos != std::string::npos ? url.substr(pathStartPos) : "/";

    return parsedUrl;
}

}
