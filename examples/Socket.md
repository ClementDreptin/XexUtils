# Socket

Connect to a server through insecure sockets and exchange data:

```C++
void Init()
{
    HRESULT hr = S_OK;

    // Create the socket
    uint16_t port = 12345;
    XexUtils::Socket socket("<ip_address>", port);

    // Connect to the server
    hr = socket.Connect();
    if (FAILED(hr))
    {
        XexUtils::Log::Error("Couldn't connect to server");
        return;
    }

    // Send a packet
    const char packet[] = "hello world";
    int bytesSent = socket.Send(packet, sizeof(packet));
    if (bytesSent != sizeof(packet))
    {
        XexUtils::Log::Error("Not all packets were sent");
        socket.Disconnect();
        return;
    }

    // Wait for the server to process the request and send a response
    Sleep(500);

    // Receive the response
    char buffer[4096] = { 0 };
    int bytesReceived = socket.Receive(buffer, sizeof(buffer));
    if (bytesReceive == -1)
    {
        XexUtils::Log::Error("Couldn't receive the server response");
        socket.Disconnect();
        return;
    }

    // Do something with what is inside buffer

    socket.Disconnect();
}
```
