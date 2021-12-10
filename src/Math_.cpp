#include "pch.h"
#include "Math_.h"


namespace XexUtils
{
namespace Math
{

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
