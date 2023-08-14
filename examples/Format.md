# Formatting

Format a string in a `printf` style:

```C++
void Init()
{
    std::string formattedString = XexUtils::Formater::Format("My favorite number is %i", 3);
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
