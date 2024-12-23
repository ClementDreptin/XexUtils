#pragma once

namespace XexUtils
{

template<typename T>
class ValueOrPtr
{
public:
    ValueOrPtr(const T &value)
        : m_Value(value), m_Ptr(nullptr), m_IsPtr(false) {}

    ValueOrPtr(T *ptr)
        : m_Value(T()), m_Ptr(ptr), m_IsPtr(true)
    {
        XASSERT(m_Ptr != nullptr);
    }

    inline const T &operator*() const { return m_IsPtr ? *m_Ptr : m_Value; }

    inline T &operator*() { return m_IsPtr ? *m_Ptr : m_Value; }

    inline T *operator&() const { return m_IsPtr ? m_Ptr : const_cast<T *>(&m_Value); }

    inline operator T() const { return operator*(); }

    inline operator T *() const { return operator&(); }

    inline ValueOrPtr<T> &operator=(const ValueOrPtr<T> &other)
    {
        operator*() = other;
        return *this;
    }

    inline ValueOrPtr<T> operator-() const { return -operator*(); }

    inline ValueOrPtr<T> operator+() const { return +operator*(); }

    inline ValueOrPtr<T> operator~() const { return ~operator*(); }

    inline ValueOrPtr<T> &operator+=(const T &value)
    {
        operator*() += value;
        return *this;
    }

    inline ValueOrPtr<T> &operator-=(const T &value)
    {
        operator*() -= value;
        return *this;
    }

    inline ValueOrPtr<T> &operator*=(const T &value)
    {
        operator*() *= value;
        return *this;
    }

    inline ValueOrPtr<T> &operator/=(const T &value)
    {
        operator*() /= value;
        return *this;
    }

    inline ValueOrPtr<T> &operator%=(const T &value)
    {
        operator*() %= value;
        return *this;
    }

    inline ValueOrPtr<T> &operator&=(const T &value)
    {
        operator*() &= value;
        return *this;
    }

    inline ValueOrPtr<T> &operator|=(const T &value)
    {
        operator*() |= value;
        return *this;
    }

    inline ValueOrPtr<T> &operator^=(const T &value)
    {
        operator*() ^= value;
        return *this;
    }

    inline ValueOrPtr<T> &operator<<=(const T &value)
    {
        operator*() <<= value;
        return *this;
    }

    inline ValueOrPtr<T> &operator>>=(const T &value)
    {
        operator*() >>= value;
        return *this;
    }

    inline ValueOrPtr<T> operator++() { return ++operator*(); }

    inline ValueOrPtr<T> operator++(int) { return operator*()++; }

    inline ValueOrPtr<T> operator--() { return --operator*(); }

    inline ValueOrPtr<T> operator--(int) { return operator*()--; }

private:
    T m_Value;
    T *m_Ptr;
    bool m_IsPtr;
};

template<typename T>
inline ValueOrPtr<T> operator+(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs + *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator-(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs - *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator*(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs * *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator/(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs / *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator%(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs % *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator&(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs & *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator|(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs | *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator^(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs ^ *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator<<(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs << *rhs;
}

template<typename T>
inline ValueOrPtr<T> operator>>(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs >> *rhs;
}

template<typename T>
inline bool operator==(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs == *rhs;
}

template<typename T>
inline bool operator!=(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs != *rhs;
}

template<typename T>
inline bool operator<(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs < *rhs;
}

template<typename T>
inline bool operator<=(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs <= *rhs;
}

template<typename T>
inline bool operator>(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs > *rhs;
}

template<typename T>
inline bool operator>=(const ValueOrPtr<T> &lhs, const ValueOrPtr<T> &rhs)
{
    return *lhs >= *rhs;
}

template<typename T>
inline std::ostream &operator<<(std::ostream &os, const ValueOrPtr<T> &value)
{
    return os << *value;
}

}
