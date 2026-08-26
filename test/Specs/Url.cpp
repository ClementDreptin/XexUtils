#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Url()
{
    Describe("Url::Parse(const std::string &)");

    It("returns null when the URL doesn't have a protocol", []() {
        auto url = Url::Parse("clearly not a url");

        TEST_EQ(url.HasValue(), false);
    });

    It("returns null when the URL has an unsupported protocol", []() {
        auto url = Url::Parse("ftp://example.com");

        TEST_EQ(url.HasValue(), false);
    });

    It("returns null when the URL is only a protocol", []() {
        auto url = Url::Parse("https://");

        TEST_EQ(url.HasValue(), false);
    });

    It("parses the scheme of a valid HTTPS URL", []() {
        auto url = Url::Parse("https://example.com");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Scheme(), UrlScheme_Https);
    });

    It("parses the scheme of a valid HTTP URL", []() {
        auto url = Url::Parse("http://example.com");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Scheme(), UrlScheme_Http);
    });

    It("parses the domain of a valid URL", []() {
        auto url = Url::Parse("https://example.com");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Domain(), "example.com");
    });

    It("sets the port to 443 for HTTPS URLs when an explicit port isn't provided", []() {
        auto url = Url::Parse("https://example.com");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Port(), 443);
    });

    It("sets the port to 80 for HTTP URLs when an explicit port isn't provided", []() {
        auto url = Url::Parse("http://example.com");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Port(), 80);
    });

    It("returns null when the URL has an invalid port", []() {
        auto url = Url::Parse("https://example.com:abc");

        TEST_EQ(url.HasValue(), false);
    });

    It("parses the port of a valid URL", []() {
        auto url = Url::Parse("https://example.com:1234");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Port(), 1234);
    });

    It("parses the path of a valid URL", []() {
        auto url = Url::Parse("https://example.com/path/to/resource");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Path(), "/path/to/resource");
    });

    It("parses a complete URL", []() {
        auto url = Url::Parse("https://example.com:1234/path/to/resource");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Scheme(), UrlScheme_Https);
        TEST_EQ(url->Domain(), "example.com");
        TEST_EQ(url->Port(), 1234);
        TEST_EQ(url->Path(), "/path/to/resource");
    });

    Describe("Url::Url(const Url &)");

    It("creates a Url from another Url", []() {
        auto url = Url::Parse("https://example.com:1234/path/to/resource").Value();
        auto copy(url);

        TEST_EQ(copy.Scheme(), UrlScheme_Https);
        TEST_EQ(copy.Domain(), "example.com");
        TEST_EQ(copy.Port(), 1234);
        TEST_EQ(copy.Path(), "/path/to/resource");
    });

    Describe("Url::operator=(const Url &)");

    It("assigns another Url to the current Url", []() {
        auto url = Url::Parse("https://example.com:1234/path/to/resource").Value();
        auto copy = url;

        TEST_EQ(copy.Scheme(), UrlScheme_Https);
        TEST_EQ(copy.Domain(), "example.com");
        TEST_EQ(copy.Port(), 1234);
        TEST_EQ(copy.Path(), "/path/to/resource");
    });

    Describe("Url::Scheme()");

    It("returns the scheme of the URL", []() {
        auto url = Url::Parse("https://example.com:1234/path/to/resource");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Scheme(), UrlScheme_Https);
    });

    Describe("Url::Domain()");

    It("returns the domain of the URL", []() {
        auto url = Url::Parse("https://example.com:1234/path/to/resource");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Domain(), "example.com");
    });

    Describe("Url::Port()");

    It("returns the port of the URL", []() {
        auto url = Url::Parse("https://example.com:1234/path/to/resource");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Port(), 1234);
    });

    Describe("Url::Path()");

    It("returns the path of the URL", []() {
        auto url = Url::Parse("https://example.com:1234/path/to/resource");

        TEST_EQ(url.HasValue(), true);
        TEST_EQ(url->Path(), "/path/to/resource");
    });
}
