# Kernel

Allow games to access the hard drive:

```C++
void Init()
{
    HRESULT hr = XexUtils::Kernel::MountHdd();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Could not mount HDD");
        return;
    }

    std::ofstream file("hdd:\\file.txt");
    if (file.is_open()) // Would return false if XexUtils::Kernel::MountHdd didn't get called
    {
        // Write something to the file..
    }

    // You can unmount the drive after you're done using it
    hr = XexUtils::Kernel::UnmountHdd();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Could not unmount HDD");
        return;
    }
}
```

Allow games to access the first USB device:

```C++
void Init()
{
    HRESULT hr = XexUtils::Kernel::MountUsb();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Could not mount USB");
        return;
    }

    std::ofstream file("usb:\\file.txt");
    if (file.is_open()) // Would return false if XexUtils::Kernel::MountUsb didn't get called
    {
        // Write something to the file..
    }

    // You can unmount the drive after you're done using it
    hr = XexUtils::Kernel::UnmountUsb();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Could not unmount USB");
        return;
    }
}
```

Detect if the console is a devkit:

```C++
void Init()
{
    if (XexUtils::Kernel::IsDevkit())
        XexUtils::Log::Print("Console is a devkit");
    else
        XexUtils::Log::Print("Console is not a devkit");
}
```

Detect if the code is running in [Xenia](https://xenia.jp/):

```C++
void Init()
{
    if (XexUtils::Kernel::InXenia())
        XexUtils::Log::Print("Code is running in Xenia");
    else
        XexUtils::Log::Print("Code is not running in Xenia");
}
```
