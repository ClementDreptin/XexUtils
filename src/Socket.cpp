#include "pch.h"
#include "Socket.h"

#include "Kernel.h"

#define WSAStartup(version, pWSAData) NetDll_WSAStartupEx((XNCALLER_TYPE)KeGetCurrentProcessType(), version, pWSAData, 2)
#define WSACleanup() NetDll_WSACleanup((XNCALLER_TYPE)KeGetCurrentProcessType())
#define XNetStartup(pXNetStartupParams) NetDll_XNetStartup((XNCALLER_TYPE)KeGetCurrentProcessType(), pXNetStartupParams)
#define inet_addr(ipAddress) NetDll_inet_addr(ipAddress)
#define socket(af, type, protocol) NetDll_socket((XNCALLER_TYPE)KeGetCurrentProcessType(), af, type, protocol)
#define setsockopt(s, level, optname, optval, optlen) NetDll_setsockopt((XNCALLER_TYPE)KeGetCurrentProcessType(), s, level, optname, optval, optlen)
#define shutdown(s, how) NetDll_shutdown((XNCALLER_TYPE)KeGetCurrentProcessType(), s, how)
#define closesocket(s) NetDll_closesocket((XNCALLER_TYPE)KeGetCurrentProcessType(), s)
#define connect(s, name, namelen) NetDll_connect((XNCALLER_TYPE)KeGetCurrentProcessType(), s, name, namelen)
#define send(s, buf, len, flags) NetDll_send((XNCALLER_TYPE)KeGetCurrentProcessType(), s, buf, len, flags)
#define recv(s, buf, len, flags) NetDll_recv((XNCALLER_TYPE)KeGetCurrentProcessType(), s, buf, len, flags)

namespace XexUtils
{

bool Socket::s_Initialized = false;
size_t Socket::s_ReferenceCounter = 0;

Socket::Socket()
{
    InitInternal("", 0);
}

Socket::Socket(const std::string &domain, uint16_t port)
{
    InitInternal(domain, port);
}

Socket::Socket(const Socket &other)
{
    InitInternal(other.m_Domain, other.m_Port);
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
    XASSERT(s_Initialized == true);

    // Resolve domain to IP address
    IN_ADDR ipAddress = DnsLookup();
    if (ipAddress.s_addr == INADDR_NONE)
        return E_FAIL;

    // Set up the address info of the server
    sockaddr_in addrInfo = {};
    addrInfo.sin_family = AF_INET;
    addrInfo.sin_port = htons(m_Port);
    addrInfo.sin_addr = ipAddress;

    // Create the socket
    m_Socket = socket(addrInfo.sin_family, SOCK_STREAM, IPPROTO_TCP);
    if (m_Socket == INVALID_SOCKET)
    {
        DebugPrint("[XexUtils][Socket]: Error: Failed to create socket: %d.", WSAGetLastError());
        return E_FAIL;
    }

    // Disable encryption
    BOOL yes = TRUE;
    if (setsockopt(m_Socket, SOL_SOCKET, 0x5801, reinterpret_cast<const char *>(&yes), sizeof(yes)) != 0)
    {
        DebugPrint("[XexUtils][Socket]: Error: Failed to disable encryption with setsockopt: %d.", WSAGetLastError());
        Disconnect();
        return E_FAIL;
    }

    // Connect to the server
    if (connect(m_Socket, reinterpret_cast<sockaddr *>(&addrInfo), sizeof(addrInfo)) == SOCKET_ERROR)
    {
        DebugPrint("[XexUtils][Socket]: Error: Failed to connect: %d.", WSAGetLastError());
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

IN_ADDR Socket::DnsLookup()
{
    XASSERT(s_Initialized == true);
    XASSERT(m_Domain.empty() == false);

    IN_ADDR address = {};
    address.s_addr = INADDR_NONE;

    XNDNS *pXNDns = nullptr;
    HANDLE hEvent = CreateEvent(nullptr, false, false, nullptr);

    // Start the domain resolution, this task is asynchronous
    int error = XNetDnsLookup(m_Domain.c_str(), hEvent, &pXNDns);
    if (error != 0)
    {
        DebugPrint("[XexUtils][Socket]: Error: XNetDnsLookup failed with code %d.", error);
        CloseHandle(hEvent);
        return address;
    }

    // Error case
    if (pXNDns->iStatus != 0 && pXNDns->iStatus != WSAEINPROGRESS)
    {
        DebugPrint("[XexUtils][Socket]: Error: Unexpected XNDNS::iStatus value: %d.", error);
        XNetDnsRelease(pXNDns);
        CloseHandle(hEvent);
        return address;
    }

    // Wait at most 5 seconds for completion
    if (pXNDns->iStatus == WSAEINPROGRESS)
        WaitForSingleObject(hEvent, 5000);

    // Check for timeout
    if (pXNDns->iStatus != 0)
    {
        DebugPrint("[XexUtils][Socket]: Error: DNS lookup for %s timed out.", m_Domain.c_str());
        XNetDnsRelease(pXNDns);
        CloseHandle(hEvent);
        return address;
    }

    address = pXNDns->aina[0];

    // Cleanup
    XNetDnsRelease(pXNDns);
    CloseHandle(hEvent);

    return address;
}

void Socket::InitInternal(const std::string &domain, uint16_t port)
{
    // Initialize the members
    m_Socket = INVALID_SOCKET;
    m_Domain = domain;
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
    err = WSAStartup(MAKEWORD(2, 2), &wsaData);
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
