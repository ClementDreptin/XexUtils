# DashLaunch

Get and set a DashLaunch option value by its name:

```C++
void Init()
{
    // Initialize the DashLaunch functions
    HRESULT hr = XexUtils::DashLaunch::Init();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Couldn't get functions from DashLaunch");
        return;
    }

    // Force liveblock to be enabled
    uint32_t liveBlockEnabled = 0;
    BOOL result = XexUtils::DashLaunch::GetOptionValueByName("liveblock", &liveBlockEnabled);
    if (result == FALSE)
    {
        XexUtils::Log::Print("Couldn't get the liveblock value from DashLaunch");
        return;
    }

    if (liveBlockEnabled == 0)
    {
        uint32_t enableLiveBlock = 1;
        result = XexUtils::DashLaunch::SetOptionValueByName("liveblock", &enableLiveBlock);
        if (result == FALSE)
        {
            XexUtils::Log::Print("Couldn't enable liveblock");
            return;
        }
    }
}
```
