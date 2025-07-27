# Path

Get the different segments of a path from a string:

```C++
void Init()
{
    XexUtils::Path path("hdd:\\path\\to\\file.txt");
    XexUtils::Path drive = path.Drive(); // hdd:
    XexUtils::Path drive = path.Basename(); // file
    XexUtils::Path drive = path.Extension(); // .txt
    XexUtils::Path drive = path.Filename(); // file.txt
    XexUtils::Path drive = path.Parent(); // hdd:\path\to
}
```

Build a path:

```C++
void Init()
{
    XexUtils::Path root("hdd:\\");
    XexUtils::Path directory("dir");
    XexUtils::Path file("file.txt");
    XexUtils::Path path = root / directory / file; // hdd:\dir\file.txt
}
```
