#include "pch.h"
#include "Math_.h"


namespace XexUtils
{
namespace Math
{

vec2 vec2::operator+(CONST vec2 &other)
{
    vec2 vec(x, y);
    vec.x += other.x;
    vec.y += other.y;

    return vec;
}

vec3 vec3::operator+(CONST vec3 &other)
{
    vec3 vec(x, y, z);
    vec.x += other.x;
    vec.y += other.y;
    vec.z += other.z;

    return vec;
}

DOUBLE Radians(DOUBLE dbDegrees)
{
    DOUBLE dbPI = 3.14159265359;
    return (dbDegrees * (dbPI / 180));
}

vec3 ToFront(CONST vec3 &origin, FLOAT fViewY, FLOAT fDistance)
{
    vec3 result;

    result.x = origin.x + (FLOAT)(fDistance * cos(Radians(fViewY)));
    result.y = origin.y + (FLOAT)(fDistance * sin(Radians(fViewY)));
    result.z = origin.z;

    return result;
}

}
}
