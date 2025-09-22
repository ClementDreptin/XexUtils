# Memory

Get a function pointer from a module through its ordinal:

```C++
void Init()
{
    typedef void (*FunctionPointerType)(int param1, int param2);
    FunctionPointerType function = static_cast<FunctionPointerType>(XexUtils::Memory::ResolveExport("xam.xex", 123));

    function();
}
```

Create a thread (like you would with the accessible Win32 API):

```C++
uint32_t Worker(void *pArgs)
{
    int number = *static_cast<int *>(pArgs);

    // Do something with number

    return 0;
}

void Init()
{
    int number = 3;

    XexUtils::Memory::Thread(reinterpret_cast<PTHREAD_START_ROUTINE>(Worker), &number);
}
```

Create a thread detached from the current running title (that will keep running even when the title stops):

```C++
uint32_t Worker(void *pArgs)
{
    int number = *static_cast<int *>(pArgs);

    // Do something with number

    return 0;
}

void Init()
{
    int number = 3;

    // The flag parameter (the third one), is the one that allows you to customize the way the thread behaves
    XexUtils::Memory::ThreadEx(reinterpret_cast<PTHREAD_START_ROUTINE>(Worker), &number, EXCREATETHREAD_SYSTEM);
}
```

Read and write to arbitrary addresses safely with no segfault:

```C++
void Init()
{
    uintptr_t address = 0x12345678;

    // If reading fails, a message will be logged to stderr and 0 is returned
    // If writing fails, a message will be logged to stderr and nothing will be done
    int previousValue = XexUtils::Memory::Read<int>(address);
    XexUtils::Memory::Write<int>(address, 3);
    int currentValue = XexUtils::Memory::Read<int>(address);
}
```
