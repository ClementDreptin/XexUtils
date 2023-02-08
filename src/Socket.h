#pragma once

namespace XexUtils
{

class Socket
{
public:
    Socket();
    Socket(const std::string &ipAddress, uint16_t port);
    Socket(const Socket &other);
    ~Socket();

    HRESULT Connect();

    void Disconnect();

    int Send(const char *buffer, size_t size);

    int Receive(char *buffer, size_t maxSize);

private:
    SOCKET m_Socket;
    std::string m_IpAddress;
    uint16_t m_Port;

    bool m_Connected;

    void InitInternal(const std::string &ipAddress, uint16_t port);

private:
    static bool s_Initialized;
    static size_t s_ReferenceCounter;

    static HRESULT Init();

    static void Cleanup();
};

}
