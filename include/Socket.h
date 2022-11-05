#pragma once

namespace XexUtils
{

// Wrapper around a SOCKET handle
class Socket
{
public:
    Socket();
    Socket(const std::string &ipAddress, uint16_t port);
    Socket(const Socket &other);
    ~Socket();

    // Establish a connection with the server.
    HRESULT Connect();

    // Disconnect from the server.
    void Disconnect();

    // Send size bytes from buffer to the server.
    int Send(const char *buffer, size_t size);

    // Receive at most maxSize bytes in buffer.
    int Receive(char *buffer, size_t maxSize);

private:
    SOCKET m_Socket;
    std::string m_IpAddress;
    uint16_t m_Port;

    bool m_Connected;

    // Common logic of the different constructors
    void InitInternal(const std::string &ipAddress, uint16_t port);

private:
    static bool s_Initialized;
    static size_t s_ReferenceCounter;

    // Initialize the Winsock library and allow communication over insecure sockets.
    static HRESULT Init();

    // Cleanup the Winsock library.
    static void Cleanup();
};

}
