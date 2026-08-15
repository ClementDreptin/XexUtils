# Formatter

Format a narrow string in a `printf` style:

```C++
void Init()
{
    std::string formattedString = XexUtils::Formatter::Format("My favorite number is %i", 3);
}
```

Format a narrow string in a `printf` style from within a variadic function:

```C++
void Init(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    std::string formattedString = XexUtils::Formatter::Format(format, args);

    va_end(args);
}
```

Format a wide string in a `wprintf` style:

```C++
void Init()
{
    std::wstring formattedWideString = XexUtils::Formatter::Format(L"My favorite number is %i", 3);
}
```

Format a wide string in a `wprintf` style from within a variadic function:

```C++
void Init(const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);

    std::wstring formattedWideString = XexUtils::Formatter::Format(format, args);

    va_end(args);
}
```

Convert a narrow string to a wide string:

```C++
void Init()
{
    std::string name = "John";
    std::wstring wideName = XexUtils::Formatter::ToWide(name);
}
```

Convert a wide string to a narrow string:

```C++
void Init()
{
    std::wstring wideName = L"John";
    std::wstring name = XexUtils::Formatter::ToNarrow(wideName);
}
```
