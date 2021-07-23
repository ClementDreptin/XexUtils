#include "pch.h"
#include "Math_.h"

namespace XexUtils
{
namespace Math
{
	double Radians(double degrees)
	{
		double pi = 3.14159265359;
		return (degrees * (pi / 180));
	}

	vec2 vec2::operator+(const vec2& other)
	{
		vec2 vec(x, y);
		vec.x += other.x;
		vec.y += other.y;

		return vec;
	}

	vec3 vec3::operator+(const vec3& other)
	{
		vec3 vec(x, y, z);
		vec.x += other.x;
		vec.y += other.y;
		vec.z += other.z;

		return vec;
	}

	vec3 ToFront(const vec3& origin, float viewY, float distance)
	{
		vec3 result;

		result.x = origin.x + (float)(distance * cos(Radians(viewY)));
		result.y = origin.y + (float)(distance * sin(Radians(viewY)));
		result.z = origin.z;

		return result;
	}
}
}