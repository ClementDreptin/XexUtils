#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Url()
{
    Describe("Url::Parse(const std::string &)");

    It("returns null when the URL doesn't have a protocol", []() {
        std::string url = "clearly not a url";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), false);
    });

    It("returns null when the URL has an unsupported protocol", []() {
        std::string url = "ftp://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), false);
    });

    It("returns null when the URL is only a protocol", []() {
        std::string url = "https://";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), false);
    });

    It("parses the scheme of a valid HTTPS URL", []() {
        std::string url = "https://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Scheme(), UrlScheme_Https);
    });

    It("parses the scheme of a valid HTTP URL", []() {
        std::string url = "http://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Scheme(), UrlScheme_Http);
    });

    It("parses the domain of a valid URL", []() {
        std::string url = "https://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Domain(), "example.com");
    });

    It("sets the port to 443 for HTTPS URLs when an explicit port isn't provided", []() {
        std::string url = "https://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Port(), 443);
    });

    It("sets the port to 80 for HTTP URLs when an explicit port isn't provided", []() {
        std::string url = "http://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Port(), 80);
    });

    It("returns null when the URL has an invalid port", []() {
        std::string url = "https://example.com:abc";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), false);
    });

    It("parses the port of a valid URL", []() {
        std::string url = "https://example.com:1234";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Port(), 1234);
    });

    It("parses the path of a valid URL", []() {
        std::string url = "https://example.com/path/to/resource";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Path(), "/path/to/resource");
    });

    It("parses a complete URL", []() {
        std::string url = "https://example.com:1234/path/to/resource";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Scheme(), UrlScheme_Https);
        TEST_EQ(parsedUrl->Domain(), "example.com");
        TEST_EQ(parsedUrl->Port(), 1234);
        TEST_EQ(parsedUrl->Path(), "/path/to/resource");
    });

    Describe("Url::Scheme()");

    It("returns the scheme of the URL", []() {
        std::string url = "https://example.com:1234/path/to/resource";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Scheme(), UrlScheme_Https);
    });

    Describe("Url::Domain()");

    It("returns the domain of the URL", []() {
        std::string url = "https://example.com:1234/path/to/resource";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Domain(), "example.com");
    });

    Describe("Url::Port()");

    It("returns the port of the URL", []() {
        std::string url = "https://example.com:1234/path/to/resource";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Port(), 1234);
    });

    Describe("Url::Path()");

    It("returns the path of the URL", []() {
        std::string url = "https://example.com:1234/path/to/resource";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Path(), "/path/to/resource");
    });
}
