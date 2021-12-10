#include "pch.h"
#include "Vec2.h"


namespace XexUtils
{
namespace Math
{

vec2::vec2()
    : x(0.0f), y(0.0f) {}

vec2::vec2(FLOAT x, FLOAT y)
    : x(x), y(y) {}

FLOAT vec2::magnitude() CONST
{
    return sqrtf(x * x + y * y);
}

VOID vec2::normalize()
{
    FLOAT mag = magnitude();
    divide(mag);
}

VOID vec2::add(CONST vec2 &other)
{
    x += other.x;
    y += other.y;
}

VOID vec2::substract(CONST vec2 &other)
{
    x -= other.x;
    y -= other.y;
}

VOID vec2::multiply(CONST vec2 &other)
{
    x *= other.x;
    y *= other.y;
}

VOID vec2::multiply(CONST FLOAT &multiplier)
{
    x *= multiplier;
    y *= multiplier;
}

VOID vec2::divide(CONST vec2 &other)
{
    x /= other.x;
    y /= other.y;
}

VOID vec2::divide(CONST FLOAT &divider)
{
    x /= divider;
    y /= divider;
}

VOID vec2::operator-()
{
    x = -x;
    y = -y;
}

bool vec2::operator==(CONST vec2 &other) CONST
{
    return x == other.x && y == other.y;
}

bool vec2::operator!=(CONST vec2 &other) CONST
{
    return x != other.x || y != other.y;
}

bool vec2::operator<(CONST vec2 &other) CONST
{
    return magnitude() < other.magnitude();
}

bool vec2::operator<=(CONST vec2 &other) CONST
{
    return magnitude() <= other.magnitude();
}

bool vec2::operator>(CONST vec2 &other) CONST
{
    return magnitude() > other.magnitude();
}

bool vec2::operator>=(CONST vec2 &other) CONST
{
    return magnitude() >= other.magnitude();
}

vec2 vec2::operator+(CONST vec2 &other) CONST
{
    return vec2(x + other.x, y + other.y);
}

vec2 vec2::operator-(CONST vec2 &other) CONST
{
    return vec2(x - other.x, y - other.y);
}

vec2 vec2::operator*(CONST vec2 &other) CONST
{
    return vec2(x * other.x, y * other.y);
}

vec2 vec2::operator*(CONST FLOAT &multiplier) CONST
{
    return vec2(x * multiplier, y * multiplier);
}

vec2 vec2::operator/(CONST vec2 &other) CONST
{
    return vec2(x / other.x, y / other.y);
}

vec2 vec2::operator/(CONST FLOAT &divider) CONST
{
    return vec2(x / divider, y / divider);
}

}
}
