#include <cstdint>
#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Socket()
{
    Describe("Socket");

    const uint8_t EC_DN[] = {
        0x30, 0x47, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
        0x02, 0x55, 0x53, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 0x04, 0x0A,
        0x13, 0x19, 0x47, 0x6F, 0x6F, 0x67, 0x6C, 0x65, 0x20, 0x54, 0x72, 0x75,
        0x73, 0x74, 0x20, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x20,
        0x4C, 0x4C, 0x43, 0x31, 0x14, 0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x03,
        0x13, 0x0B, 0x47, 0x54, 0x53, 0x20, 0x52, 0x6F, 0x6F, 0x74, 0x20, 0x52,
        0x34
    };

    const uint8_t EC_Q[] = {
        0x04, 0xF3, 0x74, 0x73, 0xA7, 0x68, 0x8B, 0x60, 0xAE, 0x43, 0xB8, 0x35,
        0xC5, 0x81, 0x30, 0x7B, 0x4B, 0x49, 0x9D, 0xFB, 0xC1, 0x61, 0xCE, 0xE6,
        0xDE, 0x46, 0xBD, 0x6B, 0xD5, 0x61, 0x18, 0x35, 0xAE, 0x40, 0xDD, 0x73,
        0xF7, 0x89, 0x91, 0x30, 0x5A, 0xEB, 0x3C, 0xEE, 0x85, 0x7C, 0xA2, 0x40,
        0x76, 0x3B, 0xA9, 0xC6, 0xB8, 0x47, 0xD8, 0x2A, 0xE7, 0x92, 0x91, 0x6A,
        0x73, 0xE9, 0xB1, 0x72, 0x39, 0x9F, 0x29, 0x9F, 0xA2, 0x98, 0xD3, 0x5F,
        0x5E, 0x58, 0x86, 0x65, 0x0F, 0xA1, 0x84, 0x65, 0x06, 0xD1, 0xDC, 0x8B,
        0xC9, 0xC7, 0x73, 0xC8, 0x8C, 0x6A, 0x2F, 0xE5, 0xC4, 0xAB, 0xD1, 0x1D,
        0x8A
    };

    const std::string domain = "jsonplaceholder.typicode.com";
    const std::string path = "/todos/1";
    const std::string request = XexUtils::Formatter::Format(
        "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "User-Agent: Xbox360/1.0\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n\r\n",
        path.c_str(),
        domain.c_str()
    );

    auto FlushSocket = [](XexUtils::Socket &socket) -> size_t {
        char buffer[2048] = {};
        size_t total = 0;

        for (;;)
        {
            int read = socket.Receive(buffer, sizeof(buffer) - 1);
            if (read <= 0)
                break;
            total += read;
        }

        return total;
    };

    It("connects using a secure socket", [&]() {
        HRESULT hr = S_OK;

        XexUtils::Socket secureSocket(domain, 443, true);
        hr = secureSocket.AddECTrustAnchor(EC_DN, sizeof(EC_DN), EC_Q, sizeof(EC_Q), XexUtils::Socket::Curve_secp384r1);
        TEST_EQ(hr, S_OK);

        hr = secureSocket.Connect();
        TEST_EQ(hr, S_OK);
    });

    It("connects using an insecure socket", [&]() {
        XexUtils::Socket secureSocket(domain, 80, false);

        HRESULT hr = secureSocket.Connect();
        TEST_EQ(hr, S_OK);
    });

    It("sends and receives data using a secure socket", [&]() {
        HRESULT hr = S_OK;

        XexUtils::Socket secureSocket(domain, 443, true);
        hr = secureSocket.AddECTrustAnchor(EC_DN, sizeof(EC_DN), EC_Q, sizeof(EC_Q), XexUtils::Socket::Curve_secp384r1);
        TEST_EQ(hr, S_OK);

        hr = secureSocket.Connect();
        TEST_EQ(hr, S_OK);

        int sent = secureSocket.Send(request.c_str(), request.size());
        TEST_EQ(sent, static_cast<int>(request.size()));

        size_t received = FlushSocket(secureSocket);
        TEST_EQ(received > 0, true);
    });

    It("sends and receives data using an insecure socket", [&]() {
        XexUtils::Socket insecureSocket(domain, 80, false);

        HRESULT hr = insecureSocket.Connect();
        TEST_EQ(hr, S_OK);

        int sent = insecureSocket.Send(request.c_str(), request.size());
        TEST_EQ(sent, static_cast<int>(request.size()));

        size_t received = FlushSocket(insecureSocket);
        TEST_EQ(received > 0, true);
    });
}
