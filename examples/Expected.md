# Expected

> [!NOTE]
> This class is a partial clone of the [C++23 `std::expected`](https://en.cppreference.com/w/cpp/utility/expected.html) compatible with the Xbox 360 compiler. The implementation is not standard compliant in the sense that not every method is implemented and the naming conventions differ, the STL uses snake-case and this class uses PascalCase.

Create an `Expected` in a success state and access its value:

```C++
void Init()
{
    XexUtils::Expected<std::string, HRESULT> stringOrError("some text");

    // Using the overloaded operators
    if (stringOrError)
    {
        std::string value = *stringOrError;
        size_t size = stringOrError->size();
        // Do something with value and size
    }

    // Using the methods
    if (stringOrError.HasValue())
    {
        std::string value = stringOrError.Value();
        size_t value = stringOrError.Value().size();
        // Do something with value and size
    }
}
```

Create an `Expected` in an error state and access its error:

```C++
void Init()
{
    XexUtils::Expected<int, std::string> intOrError(XexUtils::Unexpected<std::string>("error"));

    // Using the overloaded operator
    if (!intOrError)
    {
        std::string error = intOrError.Error();
        // Do something with error
    }

    // Using the method
    if (!intOrError.HasValue())
    {
        std::string error = intOrError.Error();
        // Do something with error
    }
}
```

Use `ValueOr()` to provide a fallback value:

```C++
void Init()
{
    XexUtils::Expected<int, std::string> success(3);
    XexUtils::Expected<int, std::string> error(XexUtils::Unexpected<std::string>("error"));

    int value1 = success.ValueOr(0); // Returns 3
    int value2 = error.ValueOr(0); // Returns 0
}
```

Use `ErrorOr()` to provide a fallback error:

```C++
void Init()
{
    XexUtils::Expected<int, std::string> error(XexUtils::Unexpected<std::string>("error"));
    XexUtils::Expected<int, std::string> success(3);

    std::string error1 = error.ErrorOr("default error"); // Returns "error"
    std::string error2 = success.ErrorOr("default error"); // Returns "default error"
}
```

Create a function that may fail:

```C++
XexUtils::Expected<int, std::string> IntOrError(bool valid)
{
    if (valid)
        return 3;

    return XexUtils::Unexpected<std::string>("error");
}
```
