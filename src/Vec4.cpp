#include "pch.h"
#include "Vec4.h"


namespace XexUtils
{
namespace Math
{

vec4::vec4()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

vec4::vec4(FLOAT x, FLOAT y, FLOAT z, FLOAT w)
    : x(x), y(y), z(z), w(0.0f) {}

FLOAT vec4::magnitude() CONST
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

VOID vec4::normalize()
{
    FLOAT mag = magnitude();
    divide(mag);
}

VOID vec4::add(CONST vec4 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
}

VOID vec4::substract(CONST vec4 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
}

VOID vec4::multiply(CONST vec4 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
}

VOID vec4::multiply(CONST FLOAT &multiplier)
{
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    w *= multiplier;
}

VOID vec4::divide(CONST vec4 &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
}

VOID vec4::divide(CONST FLOAT &divider)
{
    x /= divider;
    y /= divider;
    z /= divider;
    w /= divider;
}

VOID vec4::operator-()
{
    x = -x;
    y = -y;
    z = -z;
    w = -w;
}

bool vec4::operator==(CONST vec4 &other) CONST
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool vec4::operator!=(CONST vec4 &other) CONST
{
    return x != other.x || y != other.y || z != other.z || w != other.w;
}

bool vec4::operator<(CONST vec4 &other) CONST
{
    return magnitude() < other.magnitude();
}

bool vec4::operator<=(CONST vec4 &other) CONST
{
    return magnitude() <= other.magnitude();
}

bool vec4::operator>(CONST vec4 &other) CONST
{
    return magnitude() > other.magnitude();
}

bool vec4::operator>=(CONST vec4 &other) CONST
{
    return magnitude() >= other.magnitude();
}

vec4 vec4::operator+(CONST vec4 &other) CONST
{
    return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

vec4 vec4::operator-(CONST vec4 &other) CONST
{
    return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

vec4 vec4::operator*(CONST vec4 &other) CONST
{
    return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
}

vec4 vec4::operator*(CONST FLOAT &multiplier) CONST
{
    return vec4(x * multiplier, y * multiplier, z * multiplier, w * multiplier);
}

vec4 vec4::operator/(CONST vec4 &other) CONST
{
    return vec4(x / other.x, y / other.y, z / other.z, w / other.w);
}

vec4 vec4::operator/(CONST FLOAT &divider) CONST
{
    return vec4(x / divider, y / divider, z / divider, w / divider);
}

}
}
