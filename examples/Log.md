# Logging

Log messages to stdout and stderr:

```C++
void Init()
{
    XexUtils::Log::Info("Address is: %#010x", 0x1234);  // Print 'Info: Address is: 0x12340000' to stdout
    XexUtils::Log::Error("Error n°%i", 2);              // Print 'Error: Error n°2' to stderr
}
```

Each log function has a corresponding wide string version:

```C++
void Init()
{
    wchar_t buffer[] = L"Hello World";
    XexUtils::Log::Info(L"message: %s", buffer);  // Print 'Info: message: Hello World' to stdwout
    XexUtils::Log::Error(L"error: %s", buffer);   // Print 'Error: error: Hello World' to stdwerr
}
```
