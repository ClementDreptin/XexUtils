#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"


namespace XexUtils
{
namespace Math
{

// Convert degree to radians.
double Radians(double dbDegrees);

// Get the position at distance unit from origin.
vec3 ToFront(const vec3 &origin, float fViewY, float fDistance);

}
}
