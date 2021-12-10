#pragma once


namespace XexUtils
{
namespace Math
{

// Struct to represent a four-component vector.
struct vec4
{
    vec4();
    vec4(FLOAT x, FLOAT y, FLOAT z, FLOAT w);

    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT w;

    FLOAT magnitude() CONST;
    VOID normalize();

    VOID add(CONST vec4 &other);
    VOID substract(CONST vec4 &other);
    VOID multiply(CONST vec4 &other);
    VOID multiply(CONST FLOAT &multiplier);
    VOID divide(CONST vec4 &other);
    VOID divide(CONST FLOAT &divider);

    VOID operator-();

    bool operator==(CONST vec4 &other) CONST;
    bool operator!=(CONST vec4 &other) CONST;
    bool operator<(CONST vec4 &other) CONST;
    bool operator<=(CONST vec4 &other) CONST;
    bool operator>(CONST vec4 &other) CONST;
    bool operator>=(CONST vec4 &other) CONST;

    vec4 operator+(CONST vec4 &other) CONST;
    vec4 operator-(CONST vec4 &other) CONST;
    vec4 operator*(CONST vec4 &other) CONST;
    vec4 operator*(CONST FLOAT &multiplier) CONST;
    vec4 operator/(CONST vec4 &other) CONST;
    vec4 operator/(CONST FLOAT &divider) CONST;
};

}
}
