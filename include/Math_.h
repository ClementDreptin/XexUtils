#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace XexUtils
{
namespace Math
{

// Convert degree to radians.
float Radians(float degrees);

// Get the position at distance unit from origin.
vec3 ToFront(const vec3 &origin, float viewY, float distance);

}
}
