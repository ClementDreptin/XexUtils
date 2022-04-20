# Logging

Logging messages to stdout and stderr:
```C++
void Init()
{
    XexUtils::Log::Info("Address is: %#010x", 0x1234);  // Print 'Info: Address is: 0x12340000' to stdout
    XexUtils::Log::Error("Error n°%i", 2);              // Print 'Error: Error n°2' to stderr
}
```
