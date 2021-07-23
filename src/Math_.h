#pragma once

namespace XexUtils
{
namespace Math
{
	struct vec2
	{
		vec2() : x(0.0f), y(0.0f) {}
		vec2(float x, float y) : x(x), y(y) {}

		float x;
		float y;

		bool operator==(const vec2& other) const { return x == other.x && y == other.y; }

		vec2 operator+(const vec2& other);
	};
	
	struct vec3
	{
		vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		float x;
		float y;
		float z;

		bool operator==(const vec3& other) const { return x == other.x && y == other.y && z == other.z; }

		vec3 operator+(const vec3& other);
	};

	double Radians(double degrees);

	vec3 ToFront(const vec3& origin, float viewY, float distance);
}
}