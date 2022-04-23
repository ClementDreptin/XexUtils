# XAM (Xbox API)

Showing an Xbox notification:
```C++
void Init()
{
    XexUtils::Xam::XNotify("You just unlocked an achievement!", XexUtils::XNOTIFYQUEUEUI_TYPE::XNOTIFYUI_TYPE_ACHIEVEMENT);
}
```

Opening a keyboard to get a numerical value:
```C++
void Init()
{
    std::string strValue;
    DWORD dwResult = XexUtils::Xam::ShowKeyboard(L"Keyboard", L"Enter a value", L"123", strValue, 3, VKBD_LATIN_NUMERIC);

    if (dwResult == ERROR_CANCELLED)
        XexUtils::Log::Info("Keyboard canceled");
    else if (dwResult == ERROR_SUCCESS)
    {
        int iValue = atoi(strValue.c_str());

        // Do something with the value...
    }
}
```

Checking the current title running:
```C++
void Init()
{
    const DWORD dwDashboardTitleId = 0xFFFE07D1;
    DWORD dwCurrentTitle = XexUtils::Xam::GetCurrentTitleId();

    if (dwCurrentTitle == dwDashboardTitleId)
        XexUtils::Log::Info("Welcome to the dashboard!");
}
```

Checking that a pointer is valid before dereferencing it:
```C++
void Init()
{
    void *pdwRandomPointer = reinterpret_cast<void *>(0x12345678);

    if (XexUtils::Xam::IsAddressValid(pdwRandomPointer))
        *pdwRandomPointer = 0x123;
    else
        XexUtils::Log::Error("Segfault prevented at address: %#010x", pdwRandomPointer);
}
```
