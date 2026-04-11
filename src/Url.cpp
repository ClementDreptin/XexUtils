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
            "[XexUtils][Url]: Error: \"%s\" is not a valid URL. It doesn't contain a protocol.",
            url.c_str()
        );
        return NullOpt();
    }

    // Make sure the protocol is either "https" or "http"
    std::string protocol = url.substr(0, protocolEndPos);
    if (protocol == "https")
    {
        parsedUrl.m_Scheme = UrlScheme_Https;
        parsedUrl.m_Port = 443;
    }
    else if (protocol == "http")
    {
        parsedUrl.m_Scheme = UrlScheme_Http;
        parsedUrl.m_Port = 80;
    }
    else
    {
        DebugPrint(
            "[XexUtils][Url]: Error: \"%s\" is not a valid URL. Unknown protocol: \"%s\".",
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
            "[XexUtils][Url]: Error: \"%s\" is not a valid URL. It doesn't contain a domain.",
            url.c_str()
        );
        return NullOpt();
    }

    // Extract the domain and the port
    size_t domainEndPos = url.size();
    size_t pathStartPos = url.find('/', domainStartPos);
    size_t portStartPos = url.find(':', domainStartPos);
    bool hasPath = pathStartPos != std::string::npos;
    bool hasColon = portStartPos != std::string::npos;
    bool hasPort = hasColon && (!hasPath || portStartPos < pathStartPos);

    // Determine where the domain ends
    if (hasPort)
        domainEndPos = portStartPos;
    else if (hasPath)
        domainEndPos = pathStartPos;

    // Extract the domain
    parsedUrl.m_Domain = url.substr(domainStartPos, domainEndPos - domainStartPos);

    // Extract the port
    if (hasPort)
    {
        size_t portEndPos = hasPath ? pathStartPos : url.size();
        std::string portString = url.substr(portStartPos + 1, portEndPos - (portStartPos + 1));

        parsedUrl.m_Port = static_cast<uint16_t>(atoi(portString.c_str()));
        if (parsedUrl.m_Port == 0)
        {
            DebugPrint(
                "[XexUtils][Url]: Error: \"%s\" is not a valid URL. The port \"%s\" is invalid.",
                url.c_str(),
                portString.c_str()
            );
            return NullOpt();
        }
    }

    // Extract the path
    parsedUrl.m_Path = hasPath ? url.substr(pathStartPos) : "/";

    return parsedUrl;
}

}
