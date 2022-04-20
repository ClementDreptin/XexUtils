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

    if (dwResult == ERROR_FAILED)
        XexUtils::Log::Info("Keyboard failed"); // Should not happen
    else if (dwResult == ERROR_CANCELED)
        XexUtils::Log::Info("Keyboard canceled");
    else if (dwResult == ERROR_SUCCESS)
    {
        int iValue = atoi(strValue.c_str());

        // Do something with the value...
    }
}
```
