#include "pch.h"
#include "Math_.h"


namespace XexUtils
{
namespace Math
{

double Radians(double dbDegrees)
{
    double dbPI = 3.14159265359;
    return (dbDegrees * (dbPI / 180));
}

vec3 ToFront(const vec3 &origin, float fViewY, float fDistance)
{
    vec3 result;

    result.x = origin.x + static_cast<float>(fDistance * cos(Radians(fViewY)));
    result.y = origin.y + static_cast<float>(fDistance * sin(Radians(fViewY)));
    result.z = origin.z;

    return result;
}

}
}
