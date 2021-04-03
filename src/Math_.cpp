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