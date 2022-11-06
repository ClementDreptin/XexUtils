# XAM (Xbox API)

Show an Xbox notification:
```C++
void Init()
{
    XexUtils::Xam::XNotify("You just unlocked an achievement!", XexUtils::XNOTIFYQUEUEUI_TYPE::XNOTIFYUI_TYPE_ACHIEVEMENT);
}
```

Open a keyboard to get a numerical value:
```C++
void Init()
{
    std::string value;
    uint32_t result = XexUtils::Xam::ShowKeyboard(L"Keyboard", L"Enter a value", L"123", value, 3, VKBD_LATIN_NUMERIC);

    if (result == ERROR_CANCELLED)
        XexUtils::Log::Info("Keyboard canceled");
    else if (result == ERROR_SUCCESS)
    {
        int number = atoi(value.c_str());

        // Do something with the number...
    }
}
```

Open a message box:
```C++
void Init()
{
    const wchar_t *buttonLabels[] = { L"Yes", L"No" };
    uint32_t buttonPressedIndex = 0;

    uint32_t result = XexUtils::Xam::ShowMessageBox(
        L"Sandwich",
        L"Do you want a sandwich?",
        buttonLabels,
        ARRAYSIZE(buttonLabels),
        &buttonPressedIndex,
        XMB_ALERTICON
    );

    if (result == ERROR_CANCELLED)
        XexUtils::Log::Info("Message box canceled");
    else if (result == ERROR_SUCCESS)
        wprintf_s("User pressed %s\n", buttonLabels[buttonPressedIndex]);
}
```

Check the current title running:
```C++
void Init()
{
    const uint32_t dashboardTitleId = 0xFFFE07D1;
    uint32_t currentTitleId = XexUtils::Xam::GetCurrentTitleId();

    if (currentTitleId == dashboardTitleId)
        XexUtils::Log::Info("Welcome to the dashboard!");
}
```

Check if a pointer is valid before dereferencing it:
```C++
void Init()
{
    void *pRandomPointer = reinterpret_cast<void *>(0x12345678);

    if (XexUtils::Xam::IsAddressValid(pRandomPointer))
        *pRandomPointer = 0x123;
    else
        XexUtils::Log::Error("Segfault prevented at address: %#010x", pRandomPointer);
}
```
