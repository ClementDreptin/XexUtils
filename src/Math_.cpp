#include "pch.h"
#include "Math_.h"

namespace XexUtils
{

float Math::Radians(float degrees)
{
    return (degrees * (XM_PI / 180.0f));
}

Math::vec3 Math::ToFront(const vec3 &origin, float viewY, float distance)
{
    vec3 result;

    result.x = origin.x + distance * cos(Radians(viewY));
    result.y = origin.y + distance * sin(Radians(viewY));
    result.z = origin.z;

    return result;
}

}
