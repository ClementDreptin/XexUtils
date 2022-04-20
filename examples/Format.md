# Formatting

Formatting a string in a `printf` style:
```C++
void Init()
{
    std::string strFormattedString = XexUtils::Formater::Format("My favorite number is %i", 3);
}
```

Converting a narrow string to a wide string:
```C++
void Init()
{
    std::string strName = "John";
    std::wstring wstrName = XexUtils::Formatter::ToWide(strName);
}
```
