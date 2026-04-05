# Optional

> [!NOTE]
> This class is a partial clone of the [C++17 `std::optional`](https://en.cppreference.com/w/cpp/utility/optional.html) compatible with the Xbox 360 compiler. The implementation is not standard compliant in the sense that not every method is implemented and the naming conventions differ, the STL uses snake-case and this class uses PascalCase.

Create an `Optional` and access its value:

```C++
void Init()
{
    XexUtils::Optional<std::string> maybeString("Hello World");

    // Using the overloaded operators
    if (maybeString)
    {
        std::string value = *maybeString;
        size_t size = maybeString->size();
        // Do something with value and size
    }

    // Using the methods
    if (maybeString.HasValue())
    {
        std::string value = maybeString.Value();
        size_t size = maybeString.Value().size();
        // Do something with value and size
    }
}
```

Use `ValueOr()` to provide a fallback value:

```C++
void Init()
{
    XexUtils::Optional<int> empty;
    XexUtils::Optional<int> valid(3);

    int value1 = valid.ValueOr(0); // Returns 3
    int value2 = empty.ValueOr(0); // Returns 0
}
```

Create a function that may return a null value:

```C++
XexUtils::Optional<std::string> MaybeString(bool valid)
{
    if (valid)
        return "Hello World";

    // An empty Optional can be created from a NullOpt
    return XexUtils::NullOpt();
}
```
