# Detouring

Detouring a function:
```C++
XexUtils::Detour *FunctionDetour = nullptr;

void FunctionHook(int iParam1, int iParam2)
{
    // Do some extra stuff...

    FunctionDetour->GetOriginal<decltype(&FunctionHook)>()(iParam1, iParam2);
}

void Init()
{
    FunctionDetour = new XexUtils::Detour(0x12345678, FunctionHook);
}
```

#### Note
`Detour::GetOriginal` is a templated function that needs to be called with the function pointer type to return. This could be done automatically with templated arguments but the Xbox 360 Compiler only supports C++0x which is a draft of C++11 and templated arguments were not part of the draft yet. A templated arguments implementation would be much nicer to use:
```C++
class Detour
{
    // Rest of the class
public:
    template<typename T = void, typename... Args>
    T Original(Args... Params)
    {
        T(*OriginalFn)(Args...) = reinterpret_cast<T(*)(Args...)>(pOriginalInstructions);

        return OriginalFn(Params...);
    }
};

XexUtils::Detour *FunctionDetour = nullptr;

void FunctionHook(int iParam1, int iParam2)
{
    // Do some extra stuff...

    FunctionDetour->Original(iParam1, iParam2);
}

void Init()
{
    FunctionDetour = new XexUtils::Detour(0x12345678, FunctionHook);
}
```
