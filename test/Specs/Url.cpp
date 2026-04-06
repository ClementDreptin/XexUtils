#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Url()
{
    Describe("Url::Parse");

    It("returns null when the URL doesn't contain a protocol", []() {
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

    It("parses a valid HTTPS URL", []() {
        std::string url = "https://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Scheme(), UrlScheme_Https);
    });

    It("parses a valid HTTP URL", []() {
        std::string url = "http://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Scheme(), UrlScheme_Http);
    });

    It("parses the domain from a valid URL", []() {
        std::string url = "https://example.com";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Domain(), "example.com");
    });

    It("parses the path from a valid URL", []() {
        std::string url = "https://example.com/path/to/resource";
        auto parsedUrl = Url::Parse(url);
        TEST_EQ(parsedUrl.HasValue(), true);
        TEST_EQ(parsedUrl->Path(), "/path/to/resource");
    });
}
