#include "pch.h"
#include "Socket.h"

#include "Kernel.h"

#define WSAStartup(pWSAData) NetDll_WSAStartupEx(XNCALLER_SYSAPP, MAKEWORD(2, 2), pWSAData, 2)
#define WSACleanup() NetDll_WSACleanup(XNCALLER_SYSAPP)
#define XNetStartup(pXNetStartupParams) NetDll_XNetStartup(XNCALLER_SYSAPP, pXNetStartupParams)
#define inet_addr(ipAddress) NetDll_inet_addr(ipAddress)
#define socket(af, type, protocol) NetDll_socket(XNCALLER_SYSAPP, af, type, protocol)
#define setsockopt(s, level, optname, optval, optlen) NetDll_setsockopt(XNCALLER_SYSAPP, s, level, optname, optval, optlen)
#define shutdown(s, how) NetDll_shutdown(XNCALLER_SYSAPP, s, how)
#define closesocket(s) NetDll_closesocket(XNCALLER_SYSAPP, s)
#define connect(s, name, namelen) NetDll_connect(XNCALLER_SYSAPP, s, name, namelen)
#define send(s, buf, len, flags) NetDll_send(XNCALLER_SYSAPP, s, buf, len, flags)
#define recv(s, buf, len, flags) NetDll_recv(XNCALLER_SYSAPP, s, buf, len, flags)

namespace XexUtils
{

bool Socket::s_Initialized = false;
size_t Socket::s_ReferenceCounter = 0;

Socket::Socket()
{
    InitInternal("", 0);
}

Socket::Socket(const std::string &ipAddress, uint16_t port)
{
    InitInternal(ipAddress, port);
}

Socket::Socket(const Socket &other)
{
    InitInternal(other.m_IpAddress, other.m_Port);
}

Socket::~Socket()
{
    Disconnect();

    if (s_ReferenceCounter != 0)
        s_ReferenceCounter--;

    // Once the amount of instances hits 0, execute the global cleanup
    if (s_ReferenceCounter == 0)
        Cleanup();
}

HRESULT Socket::Connect()
{
    if (!s_Initialized)
        return E_FAIL;

    sockaddr_in addrInfo = {};

    // Set up the address info of the server
    addrInfo.sin_family = AF_INET;
    addrInfo.sin_port = htons(m_Port);
    addrInfo.sin_addr.s_addr = inet_addr(m_IpAddress.c_str());

    if (addrInfo.sin_addr.s_addr == INADDR_NONE)
        return E_FAIL;

    // Create the socket
    m_Socket = socket(addrInfo.sin_family, SOCK_STREAM, IPPROTO_TCP);
    if (m_Socket == INVALID_SOCKET)
        return E_FAIL;

    // Disable encryption
    BOOL yes = TRUE;
    if (setsockopt(m_Socket, SOL_SOCKET, 0x5801, reinterpret_cast<const char *>(&yes), sizeof(yes)) != 0)
    {
        Disconnect();
        return E_FAIL;
    }

    // Set the socket timeout to 2 seconds
    timeval tv = { 2, 0 };
    if (setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&tv), sizeof(timeval)) != 0)
    {
        Disconnect();
        return E_FAIL;
    }

    // Connect to the server
    if (connect(m_Socket, reinterpret_cast<sockaddr *>(&addrInfo), sizeof(addrInfo)) == SOCKET_ERROR)
    {
        Disconnect();
        return E_FAIL;
    }

    m_Connected = true;

    return S_OK;
}

void Socket::Disconnect()
{
    if (m_Socket != INVALID_SOCKET)
    {
        shutdown(m_Socket, SD_BOTH);
        closesocket(m_Socket);
    }

    m_Connected = false;
}

int Socket::Send(const char *buffer, size_t size)
{
    XASSERT(m_Connected == true);

    // Send the bytes from buffer in the socket
    return send(m_Socket, buffer, size, 0);
}

int Socket::Receive(char *buffer, size_t maxSize)
{
    XASSERT(m_Connected == true);

    // Receive at most maxSize bytes in buffer.
    return recv(m_Socket, buffer, maxSize, 0);
}

void Socket::InitInternal(const std::string &ipAddress, uint16_t port)
{
    XASSERT(port != 0);

    // Initialize the members
    m_Socket = INVALID_SOCKET;
    m_IpAddress = ipAddress;
    m_Port = port;
    m_Connected = false;

    s_ReferenceCounter++;

    // Execute the global initialization when creating the first Socket instance
    if (s_ReferenceCounter == 1)
        Init();
}

HRESULT Socket::Init()
{
    WSADATA wsaData = {};
    XNetStartupParams xNetStartupParams = {};

    // Bypass security
    xNetStartupParams.cfgSizeOfStruct = sizeof(XNetStartupParams);
    xNetStartupParams.cfgFlags = XNET_STARTUP_BYPASS_SECURITY;

    // Initialize XNet
    int err = XNetStartup(&xNetStartupParams);
    if (err != 0)
    {
        DebugPrint("[XexUtils][Socket]: Error: XNetStartup failed with code %d.", err);
        return E_FAIL;
    }

    // Initialize Winsock
    err = WSAStartup(&wsaData);
    if (err != 0)
    {
        DebugPrint("[XexUtils][Socket]: Error: WSAStartup failed with code %d.", err);
        return E_FAIL;
    }

    s_Initialized = true;

    return S_OK;
}

void Socket::Cleanup()
{
    WSACleanup();
}

}
