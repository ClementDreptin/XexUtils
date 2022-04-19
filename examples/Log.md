# Logging

```C++
void Init()
{
    XexUtils::Log::Info("Address is: %08X", 0x1234);  // Print 'Address is: 0x12340000' to stdout
    XexUtils::Log::Error("Error n°%i", 2);            // Print 'Error n°2' to stderr
}
```
