#pragma once


namespace XexUtils
{
namespace Math
{

// Struct to represent a two-component vector.
struct vec2
{
    vec2();
    vec2(FLOAT x, FLOAT y);

    FLOAT x;
    FLOAT y;

    FLOAT magnitude() CONST;
    VOID normalize();

    VOID add(CONST vec2 &other);
    VOID substract(CONST vec2 &other);
    VOID multiply(CONST vec2 &other);
    VOID multiply(CONST FLOAT &multiplier);
    VOID divide(CONST vec2 &other);
    VOID divide(CONST FLOAT &divider);

    VOID operator-();

    bool operator==(CONST vec2 &other) CONST;
    bool operator!=(CONST vec2 &other) CONST;
    bool operator<(CONST vec2 &other) CONST;
    bool operator<=(CONST vec2 &other) CONST;
    bool operator>(CONST vec2 &other) CONST;
    bool operator>=(CONST vec2 &other) CONST;

    vec2 operator+(CONST vec2 &other) CONST;
    vec2 operator-(CONST vec2 &other) CONST;
    vec2 operator*(CONST vec2 &other) CONST;
    vec2 operator*(CONST FLOAT &multiplier) CONST;
    vec2 operator/(CONST vec2 &other) CONST;
    vec2 operator/(CONST FLOAT &divider) CONST;
};

}
}
