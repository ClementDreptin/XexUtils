# Filesystem

Allow games to access the hard drive:

```C++
void Init()
{
    HRESULT hr = XexUtils::Fs::MountHdd();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Could not mount HDD");
        return;
    }

    std::ofstream file("hdd:\\file.txt");
    if (file.is_open()) // Would return false if XexUtils::Fs::MountHdd didn't get called
    {
        // Write something to the file..
    }

    // You can unmount the drive after you're done using it
    hr = XexUtils::Fs::UnmountHdd();
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
    HRESULT hr = XexUtils::Fs::MountUsb();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Could not mount USB");
        return;
    }

    std::ofstream file("usb:\\file.txt");
    if (file.is_open()) // Would return false if XexUtils::Fs::MountUsb didn't get called
    {
        // Write something to the file..
    }

    // You can unmount the drive after you're done using it
    hr = XexUtils::Fs::UnmountUsb();
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Could not unmount USB");
        return;
    }
}
```

Get the different segments of a path from a string:

```C++
void Init()
{
    XexUtils::Fs::Path path("hdd:\\path\\to\\file.txt");
    XexUtils::Fs::Path drive = path.Drive(); // hdd:
    XexUtils::Fs::Path drive = path.Basename(); // file
    XexUtils::Fs::Path drive = path.Extension(); // .txt
    XexUtils::Fs::Path drive = path.Filename(); // file.txt
    XexUtils::Fs::Path drive = path.Parent(); // hdd:\path\to
}
```

Build a path:

```C++
void Init()
{
    XexUtils::Fs::Path root("hdd:\\");
    XexUtils::Fs::Path directory("dir");
    XexUtils::Fs::Path file("file.txt");
    XexUtils::Fs::Path path = root / directory / file; // hdd:\dir\file.txt
}
```

List all the files within a directory:

```C++
void Init()
{
    XexUtils::Optional<std::vector<WIN32_FIND_DATA>> files = XexUtils::Fs::ReadDirectory(
        "hdd:\\path\\to\\dir"
    );
    if (!files)
    {
        XexUtils::Log::Print("Could not list the files.");
        return;
    }

    for (size_t i = 0; i < files->size(); i++)
    {
        // Check the Microsoft documentation for the list of all available fields:
        // https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-win32_find_dataa
        XexUtils::Log::Print("filename: %s", (*files)[i].cFileName);
    }
}
```
