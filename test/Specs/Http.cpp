#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Http()
{
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

    Describe("Http::Client::Get");

    It("sends a GET request over HTTP", []() {
        Http::Client client;
        auto response = client.Get("http://jsonplaceholder.typicode.com/todos/1");

        std::string expectedResponse =
            "{\n"
            "  \"userId\": 1,\n"
            "  \"id\": 1,\n"
            "  \"title\": \"delectus aut autem\",\n"
            "  \"completed\": false\n"
            "}";

        TEST_EQ(response.HasValue(), true);
        TEST_EQ(response->Status, 200);
        TEST_EQ(response->Body, expectedResponse);
    });

    It("sends a GET request over HTTPS", [&]() {
        Http::Client client;
        client.AddECTrustAnchor(EC_DN, sizeof(EC_DN), EC_Q, sizeof(EC_Q), Socket::Curve_secp384r1);

        auto response = client.Get("https://jsonplaceholder.typicode.com/todos/1");

        std::string expectedResponse =
            "{\n"
            "  \"userId\": 1,\n"
            "  \"id\": 1,\n"
            "  \"title\": \"delectus aut autem\",\n"
            "  \"completed\": false\n"
            "}";

        TEST_EQ(response.HasValue(), true);
        TEST_EQ(response->Status, 200);
        TEST_EQ(response->Body, expectedResponse);
    });

    It("sends a GET from a Url object", [&]() {
        Http::Client client;
        client.AddECTrustAnchor(EC_DN, sizeof(EC_DN), EC_Q, sizeof(EC_Q), Socket::Curve_secp384r1);

        auto url = Url::Parse("https://jsonplaceholder.typicode.com/todos/1");
        auto response = client.Get(*url);

        std::string expectedResponse =
            "{\n"
            "  \"userId\": 1,\n"
            "  \"id\": 1,\n"
            "  \"title\": \"delectus aut autem\",\n"
            "  \"completed\": false\n"
            "}";

        TEST_EQ(response.HasValue(), true);
        TEST_EQ(response->Status, 200);
        TEST_EQ(response->Body, expectedResponse);
    });

    It("sends a GET request with custom headers", [&]() {
        Http::Client client;

        Http::RequestOptions options(*Url::Parse("http://httpbin.org/headers"));
        options.Headers["X-Custom-Header"] = "CustomValue";
        auto response = client.Get(options);

        bool responseContainsCustomHeader =
            response->Body.find("\"X-Custom-Header\": \"CustomValue\"") != std::string::npos;

        TEST_EQ(response.HasValue(), true);
        TEST_EQ(response->Status, 200);
        TEST_EQ(responseContainsCustomHeader, true);
    });

    It("follows redirects to the same domain", [&]() {
        Http::Client client;
        client.AddECTrustAnchor(EC_DN, sizeof(EC_DN), EC_Q, sizeof(EC_Q), Socket::Curve_secp384r1);

        std::string url = "http://httpbin.org/redirect-to?url=http%3A%2F%2Fhttpbin.org%2Fstatus%2F200";
        auto response = client.Get(url);

        TEST_EQ(response.HasValue(), true);
        TEST_EQ(response->Status, 200);
    });
}
