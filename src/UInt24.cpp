#include "pch.h"
#include "UInt24.h"

namespace XexUtils
{

UInt24::UInt24()
{
    ZeroMemory(&m_Data, sizeof(m_Data));
}

UInt24::UInt24(uint32_t value)
{
    Assign(value);
}

UInt24::UInt24(const uint8_t (&bytes)[3])
{
    Assign((bytes[0] << 16) | (bytes[1] << 8) | bytes[2]);
}

UInt24 &UInt24::operator=(uint32_t value)
{
    Assign(value);
    return *this;
}

UInt24 &UInt24::operator=(const uint8_t (&bytes)[3])
{
    Assign((bytes[0] << 16) | (bytes[1] << 8) | bytes[2]);
    return *this;
}

uint32_t UInt24::AsUInt32() const
{
    return static_cast<uint32_t>(m_Data[0]) |
           (static_cast<uint32_t>(m_Data[1]) << 8) |
           (static_cast<uint32_t>(m_Data[2]) << 16);
}

UInt24 UInt24::operator+() const
{
    return *this;
}

UInt24 UInt24::operator~() const
{
    return UInt24(~AsUInt32() & 0xFFFFFF);
}

UInt24 &UInt24::operator++()
{
    Assign(AsUInt32() + 1);
    return *this;
}

UInt24 UInt24::operator++(int)
{
    UInt24 tmp(*this);
    ++(*this);
    return tmp;
}

UInt24 &UInt24::operator--()
{
    Assign(AsUInt32() - 1);
    return *this;
}

UInt24 UInt24::operator--(int)
{
    UInt24 tmp(*this);
    --(*this);
    return tmp;
}

UInt24 &UInt24::operator+=(const UInt24 &other)
{
    Assign(AsUInt32() + other.AsUInt32());
    return *this;
}

UInt24 &UInt24::operator-=(const UInt24 &other)
{
    Assign(AsUInt32() - other.AsUInt32());
    return *this;
}

UInt24 &UInt24::operator*=(const UInt24 &other)
{
    Assign(AsUInt32() * other.AsUInt32());
    return *this;
}

UInt24 &UInt24::operator/=(const UInt24 &other)
{
    XASSERT(other.AsUInt32() != 0);
    Assign(AsUInt32() / other.AsUInt32());
    return *this;
}

UInt24 &UInt24::operator%=(const UInt24 &other)
{
    XASSERT(other.AsUInt32() != 0);
    Assign(AsUInt32() % other.AsUInt32());
    return *this;
}

UInt24 &UInt24::operator&=(const UInt24 &other)
{
    Assign(AsUInt32() & other.AsUInt32());
    return *this;
}

UInt24 &UInt24::operator|=(const UInt24 &other)
{
    Assign(AsUInt32() | other.AsUInt32());
    return *this;
}

UInt24 &UInt24::operator^=(const UInt24 &other)
{
    Assign(AsUInt32() ^ other.AsUInt32());
    return *this;
}

UInt24 &UInt24::operator<<=(int shift)
{
    Assign(AsUInt32() << shift);
    return *this;
}

UInt24 &UInt24::operator>>=(int shift)
{
    Assign(AsUInt32() >> shift);
    return *this;
}

UInt24 operator+(UInt24 a, const UInt24 &b)
{
    a += b;
    return a;
}

UInt24 operator-(UInt24 a, const UInt24 &b)
{
    a -= b;
    return a;
}

UInt24 operator*(UInt24 a, const UInt24 &b)
{
    a *= b;
    return a;
}

UInt24 operator/(UInt24 a, const UInt24 &b)
{
    a /= b;
    return a;
}

UInt24 operator%(UInt24 a, const UInt24 &b)
{
    a %= b;
    return a;
}

UInt24 operator&(UInt24 a, const UInt24 &b)
{
    a &= b;
    return a;
}

UInt24 operator|(UInt24 a, const UInt24 &b)
{
    a |= b;
    return a;
}

UInt24 operator^(UInt24 a, const UInt24 &b)
{
    a ^= b;
    return a;
}

UInt24 operator<<(UInt24 a, int shift)
{
    a <<= shift;
    return a;
}

UInt24 operator>>(UInt24 a, int shift)
{
    a >>= shift;
    return a;
}

bool operator==(const UInt24 &a, const UInt24 &b)
{
    return a.AsUInt32() == b.AsUInt32();
}

bool operator!=(const UInt24 &a, const UInt24 &b)
{
    return !(a == b);
}

bool operator<(const UInt24 &a, const UInt24 &b)
{
    return a.AsUInt32() < b.AsUInt32();
}

bool operator>(const UInt24 &a, const UInt24 &b)
{
    return b < a;
}

bool operator<=(const UInt24 &a, const UInt24 &b)
{
    return !(b < a);
}

bool operator>=(const UInt24 &a, const UInt24 &b)
{
    return !(a < b);
}

std::ostream &operator<<(std::ostream &os, const UInt24 &value)
{
    return os << value.AsUInt32();
}

std::istream &operator>>(std::istream &is, UInt24 &value)
{
    uint32_t tmp;
    if (is >> tmp)
        value = UInt24(tmp);
    return is;
}

void UInt24::Assign(uint32_t value)
{
    value &= 0xFFFFFF;
    m_Data[0] = static_cast<uint8_t>(value & 0xFF);
    m_Data[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    m_Data[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
}

}
