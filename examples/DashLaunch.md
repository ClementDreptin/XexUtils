# Dashlaunch

Get and set a Dashlaunch option value by its name:

```C++
void Init()
{
    // Initialize the Dashlaunch functions
    HRESULT hr = XexUtils::Dashlaunch::Init();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Couldn't get functions from Dashlaunch");
        return;
    }

    // Force liveblock to be enabled
    uint32_t liveBlockEnabled = 0;
    BOOL result = XexUtils::Dashlaunch::GetOptionValueByName("liveblock", &liveBlockEnabled);
    if (result == FALSE)
    {
        XexUtils::Log::Print("Couldn't get the liveblock value from Dashlaunch");
        return;
    }

    if (liveBlockEnabled == 0)
    {
        uint32_t enableLiveBlock = 1;
        result = XexUtils::Dashlaunch::SetOptionValueByName("liveblock", &enableLiveBlock);
        if (result == FALSE)
        {
            XexUtils::Log::Print("Couldn't enable liveblock");
            return;
        }
    }
}
```
