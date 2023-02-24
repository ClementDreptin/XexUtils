#pragma once

namespace XexUtils
{

template<typename T>
class ValueOrPtr
{
public:
    ValueOrPtr(const T &value)
        : m_Value(value), m_Ptr(nullptr), m_Index(0) {}

    ValueOrPtr(T *ptr)
        : m_Value(T()), m_Ptr(ptr), m_Index(1) {}

    inline const T &operator*() const { return isPtr() ? *m_Ptr : m_Value; }

    inline T *operator&() const { return isPtr() ? m_Ptr : const_cast<T *>(&m_Value); }

    inline T operator=(const T &value) { return isPtr() ? *m_Ptr = value : m_Value = value; }

    inline T operator+(const T &value) { return isPtr() ? *m_Ptr + value : m_Value + value; }

    inline const T &operator+=(const T &value) { return isPtr() ? *m_Ptr += value : m_Value += value; }

    inline T operator-(const T &value) { return isPtr() ? *m_Ptr - value : m_Value - value; }

    inline const T &operator-=(const T &value) { return isPtr() ? *m_Ptr -= value : m_Value -= value; }

private:
    T m_Value;
    T *m_Ptr;
    uint8_t m_Index;

    bool isPtr() const { return m_Index == 1; }
};

}
