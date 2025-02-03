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
        XexUtils::Log::Print("Keyboard canceled");
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
        XexUtils::Log::Print("Message box canceled");
    else if (result == ERROR_SUCCESS)
        wprintf_s(L"User pressed %s\n", buttonLabels[buttonPressedIndex]);
}
```

Check the current title running:

```C++
void Init()
{
    const uint32_t dashboardTitleId = 0xFFFE07D1;
    uint32_t currentTitleId = XexUtils::Xam::GetCurrentTitleId();

    if (currentTitleId == dashboardTitleId)
        XexUtils::Log::Print("Welcome to the dashboard!");
}
```

Check if a pointer is valid before dereferencing it:

```C++
void Init()
{
    uint32_t *pRandomPointer = reinterpret_cast<uint32_t *>(0x12345678);

    if (XexUtils::Xam::IsAddressValid(pRandomPointer))
        *pRandomPointer = 0x123;
    else
        XexUtils::Log::Print("Segfault prevented at address: %#010x", pRandomPointer);
}
```

Allow games to access the hard drive:

```C++
void Init()
{
    HRESULT hr = XexUtils::Xam::MountHdd();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Could not mount HDD");
        return;
    }

    std::ofstream file("hdd:\\file.txt");
    if (file.is_open()) // Would return false if XexUtils::Xam::MountHdd didn't get called
    {
        // Write something to the file..
    }
}
```

Detect if the console is a devkit:

```C++
void Init()
{
    if (XexUtils::Xam::IsDevkit())
        XexUtils::Log::Print("Console is a devkit");
    else
        XexUtils::Log::Print("Console is not a devkit");
}
```

Detect if the code is running in [Xenia](https://xenia.jp/):

```C++
void Init()
{
    if (XexUtils::Xam::InXenia())
        XexUtils::Log::Print("Code is running in Xenia");
    else
        XexUtils::Log::Print("Code is not running in Xenia");
}
```
