#pragma once


namespace XexUtils
{
namespace Math
{

// Struct to represent a three-component vector.
struct vec3
{
    vec3();
    vec3(FLOAT x, FLOAT y, FLOAT z);

    FLOAT x;
    FLOAT y;
    FLOAT z;

    FLOAT magnitude() CONST;
    VOID normalize();

    VOID add(CONST vec3 &other);
    VOID substract(CONST vec3 &other);
    VOID multiply(CONST vec3 &other);
    VOID multiply(CONST FLOAT &multiplier);
    VOID divide(CONST vec3 &other);
    VOID divide(CONST FLOAT &divider);

    VOID operator-();

    bool operator==(CONST vec3 &other) CONST;
    bool operator!=(CONST vec3 &other) CONST;
    bool operator<(CONST vec3 &other) CONST;
    bool operator<=(CONST vec3 &other) CONST;
    bool operator>(CONST vec3 &other) CONST;
    bool operator>=(CONST vec3 &other) CONST;

    vec3 operator+(CONST vec3 &other) CONST;
    vec3 operator-(CONST vec3 &other) CONST;
    vec3 operator*(CONST vec3 &other) CONST;
    vec3 operator*(CONST FLOAT &multiplier) CONST;
    vec3 operator/(CONST vec3 &other) CONST;
    vec3 operator/(CONST FLOAT &divider) CONST;
};

}
}
