#include "pch.h"
#include "Vec3.h"


namespace XexUtils
{
namespace Math
{

vec3::vec3()
    : x(0.0f), y(0.0f), z(0.0f) {}

vec3::vec3(FLOAT x, FLOAT y, FLOAT z)
    : x(x), y(y), z(z) {}

FLOAT vec3::magnitude() CONST
{
    return sqrtf(x * x + y * y + z * z);
}

VOID vec3::normalize()
{
    FLOAT mag = magnitude();
    divide(mag);
}

VOID vec3::add(CONST vec3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}

VOID vec3::substract(CONST vec3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

VOID vec3::multiply(CONST vec3 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
}

VOID vec3::multiply(CONST FLOAT &multiplier)
{
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
}

VOID vec3::divide(CONST vec3 &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
}

VOID vec3::divide(CONST FLOAT &divider)
{
    x /= divider;
    y /= divider;
    z /= divider;
}

VOID vec3::operator-()
{
    x = -x;
    y = -y;
    z = -z;
}

bool vec3::operator==(CONST vec3 &other) CONST
{
    return x == other.x && y == other.y && z == other.z;
}

bool vec3::operator!=(CONST vec3 &other) CONST
{
    return x != other.x || y != other.y || z != other.z;
}

bool vec3::operator<(CONST vec3 &other) CONST
{
    return magnitude() < other.magnitude();
}

bool vec3::operator<=(CONST vec3 &other) CONST
{
    return magnitude() <= other.magnitude();
}

bool vec3::operator>(CONST vec3 &other) CONST
{
    return magnitude() > other.magnitude();
}

bool vec3::operator>=(CONST vec3 &other) CONST
{
    return magnitude() >= other.magnitude();
}

vec3 vec3::operator+(CONST vec3 &other) CONST
{
    return vec3(x + other.x, y + other.y, z + other.z);
}

vec3 vec3::operator-(CONST vec3 &other) CONST
{
    return vec3(x - other.x, y - other.y, z - other.z);
}

vec3 vec3::operator*(CONST vec3 &other) CONST
{
    return vec3(x * other.x, y * other.y, z * other.z);
}

vec3 vec3::operator*(CONST FLOAT &multiplier) CONST
{
    return vec3(x * multiplier, y * multiplier, z * multiplier);
}

vec3 vec3::operator/(CONST vec3 &other) CONST
{
    return vec3(x / other.x, y / other.y, z / other.z);
}

vec3 vec3::operator/(CONST FLOAT &divider) CONST
{
    return vec3(x / divider, y / divider, z / divider);
}

}
}
