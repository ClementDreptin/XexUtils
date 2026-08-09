# UInt24

Create a 24-bit unsigned integer and perform basic arithmetic on it (check the [UInt24](../src/UInt24.h) class to see all of the available operations):

```C++
void Init()
{
    XexUtils::UInt24 a(10);
    XexUtils::UInt24 b(20);

    XexUtils::UInt24 c = a + b; // 30
    XexUtils::UInt24 d = b - a; // 10
    XexUtils::UInt24 e = a * b; // 200
}
```

Values wrap around like any other unsigned integer type when they exceed the 24-bit range:

```C++
void Init()
{
    XexUtils::UInt24 value(0xFFFFFF); // The maximum value a UInt24 can hold.

    ++value; // Wraps around to 0.
}
```

Construct a `UInt24` from a big-endian byte array, which is useful when reading 24-bit values directly out of a file format:

```C++
void Init()
{
    const uint8_t bytes[] = { 0x12, 0x34, 0x56 };
    XexUtils::UInt24 value(bytes); // 0x123456
}
```

Write a `UInt24` to, or read one from, a stream:

```C++
void Init()
{
    XexUtils::UInt24 value(42);

    std::cout << value; // prints "42"

    std::istringstream is("123");
    is >> value; // value is now 123
}
```
