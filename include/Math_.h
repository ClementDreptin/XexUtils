#pragma once


namespace XexUtils
{
namespace Math
{

//--------------------------------------------------------------------------------------
// Name: struct vec2
// Desc: Struct to represent a two-component vector.
//--------------------------------------------------------------------------------------
struct vec2
{
    vec2() : x(0.0f), y(0.0f) {}
    vec2(FLOAT x, FLOAT y) : x(x), y(y) {}

    FLOAT x;
    FLOAT y;

    bool operator==(CONST vec2& other) CONST { return x == other.x && y == other.y; }

    vec2 operator+(CONST vec2& other);
};


//--------------------------------------------------------------------------------------
// Name: struct vec3
// Desc: Struct to represent a three-component vector.
//--------------------------------------------------------------------------------------
struct vec3
{
    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(FLOAT x, FLOAT y, FLOAT z) : x(x), y(y), z(z) {}

    FLOAT x;
    FLOAT y;
    FLOAT z;

    bool operator==(CONST vec3& other) CONST { return x == other.x && y == other.y && z == other.z; }

    vec3 operator+(CONST vec3& other);
};


DOUBLE Radians(DOUBLE dbDegrees);


vec3 ToFront(CONST vec3& origin, FLOAT fViewY, FLOAT fDistance);

}
}