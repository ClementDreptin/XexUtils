#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace XexUtils
{
namespace Math
{

float Radians(float degrees);

vec3 ProjectForward(const vec3 &origin, float viewY, float distance);

template<uint32_t N>
uint32_t RoundToNextMultipleOf(uint32_t base)
{
    return (base + N) & ~(N - 1); // Believe it or not, it works
}

}
}
