# Kernel functions

Checking the current title running:
```C++
void Init()
{
    const DWORD dwDashboardTitleId = 0xFFFE07D1;
    DWORD dwCurrentTitle = XexUtils::Kernel::XamGetCurrentTitleId();

    if (dwCurrentTitle == dwDashboardTitleId)
        XexUtils::Log::Info("Welcome to the dashboard!");
}
```

Checking that a pointer is valid before dereferencing it:
```C++
void Init()
{
    void *pdwRandomPointer = reinterpret_cast<void *>(0x12345678);

    if (XexUtils::Kernel::MmIsAddressValid(pdwRandomPointer))
        *pdwRandomPointer = 0x123;
    else
        XexUtils::Log::Error("Segfault prevented at address: %#010x", pdwRandomPointer);
}
```
