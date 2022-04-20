# Memory

Getting a function pointer from a module through its ordinal:
```C++
void Init()
{
    typedef void (*FunctionPointerType)(int iParam1, int iParam2);
    FunctionPointerType Function = reinterpret_cast<FunctionPointerType>(XexUtils::Memory::ResolveFunction("xam.xex", 123));

    Function();
}
```

Creating a thread (like you would with the accessible Win32 API):
```C++
DWORD Worker(void *pParam)
{
    DWORD dwParam = reinterpret_cast<DWORD>(pParam);

    // Do something with dwParam

    return 0;
}

void Init()
{
    DWORD dwParam = 3;

    XexUtils::Memory::Thread(reinterpret_cast<PTHREAD_START_ROUTINE>(Worker), &dwParam);
}
```

Creating a thread detached from the current running title (that will keep running even when the title stops):
```C++
DWORD Worker(void *pParam)
{
    DWORD dwParam = reinterpret_cast<DWORD>(pParam);

    // Do something with dwParam

    return 0;
}

void Init()
{
    // The flag parameter (the third one), is the one that allows you to customize the way the thread behaves
    XexUtils::Memory::ThreadEx(reinterpret_cast<PTHREAD_START_ROUTINE>(Worker), &dwParam, 2);
}
```

Reading and writing to arbitrary addresses safely with no segfault:
```C++
void Init()
{
    DWORD dwAddress = 0x12345678;

    // If reading fails, a message will be logged to stderr and 0 is returned
    // If writing fails, a message will be logged to stderr and nothing will be done
    DWORD dwPreviousValue = XexUtils::Memory::Read<DWORD>(dwAddress);
    XexUtils::Memory::Write<DWORD>(dwAddress, 3);
    DWORD dwCurrentValue = XexUtils::Memory::Read<DWORD>(dwAddress);
}
```
