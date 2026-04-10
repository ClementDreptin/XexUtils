# Url

Parse an URL from a string:

```C++
void Init()
{
    std::string url = "https://example.com:1234/path/to/resource";
    XexUtils::Optional<XexUtils::Url> parsedUrl = Url::Parse(url);
    if (!parsedUrl)
    {
        XexUtils::Log::Print("%s is not a valid URL.", url.c_str());
        return;
    }

    parsedUrl->Scheme(); // UrlScheme_Https (0)
    parsedUrl->Domain(); // "example.com"
    parsedUrl->Port();   // 1234
    parsedUrl->Path();   // "/path/to/resource"
}
```

> [!IMPORTANT]
> The `XexUtils::Url` class has no public constructor, you need to use `XexUtils::Url::Parse` to create `XexUtils::Url` instances.
