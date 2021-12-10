#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"


namespace XexUtils
{
namespace Math
{

// Convert degree to radians.
DOUBLE Radians(DOUBLE dbDegrees);

// Get the position at distance unit from origin.
vec3 ToFront(CONST vec3 &origin, FLOAT fViewY, FLOAT fDistance);

}
}
