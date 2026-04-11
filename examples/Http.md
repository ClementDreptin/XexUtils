# Http

Send a GET request:

```C++
void Init()
{
    XexUtils::Http::Client httpClient;

    // Add an Elliptic Curve trust anchor (only necessary when using a HTTPS)
    const uint8_t dn[] = { 0x1, 0x2, 0x3 };
    const uint8_t q[] = { 0x1, 0x2, 0x3 };
    httpClient.AddECTrustAnchor(dn, sizeof(dn), q, sizeof(q), XexUtils::Socket::Curve_secp384r1);

    // Send the request
    XexUtils::Optional<XexUtils::Http::Response> response = httpClient.Get("https://example.com/");
    if (!response)
    {
        XexUtils::Log::Print("Sending GET request failed.");
        return;
    }

    // Check the status code
    if (response->Status != 200)
    {
        XexUtils::Log::Print("Unexpected status code: %i", response->Status);
        return;
    }

    response->Body; // std::vector<uint8_t>
    response->BodyAsString(); // std::string
}
```

Send a POST request:

```C++
void Init()
{
    XexUtils::Http::Client httpClient;

    // Send the request
    XexUtils::Optional<XexUtils::Http::Response> response = httpClient.Post("http://example.com/", "my custom body");
    if (!response)
    {
        XexUtils::Log::Print("Sending POST request failed.");
        return;
    }

    // Check the status code
    if (response->Status != 201)
    {
        XexUtils::Log::Print("Unexpected status code: %i", response->Status);
        return;
    }

    response->Body; // std::vector<uint8_t>
    response->BodyAsString(); // std::string
}
```

Send a request with custom headers:

```C++
void Init()
{
    XexUtils::Http::Client httpClient;

    // Create the request options
    XexUtils::Http::RequestOptions options(*XexUtils::Url::Parse("http://example.com/"));
    options.Method = XexUtils::Http::Method_Get;
    options.Headers["X-Custom-Header"] = "CustomValue";

    // Send the request
    XexUtils::Optional<XexUtils::Http::Response> response = httpClient.SendRequest(options);
    if (!response)
    {
        XexUtils::Log::Print("Sending POST request failed.");
        return;
    }

    // Check the status code
    if (response->Status != 200)
    {
        XexUtils::Log::Print("Unexpected status code: %i", response->Status);
        return;
    }

    response->Body; // std::vector<uint8_t>
    response->BodyAsString(); // std::string
}
```

### How to generate the trust anchor data

See [Generate Trust Anchors](./generate-trust-anchors.md).
