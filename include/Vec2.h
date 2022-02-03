#pragma once


namespace XexUtils
{
namespace Math
{

// Struct to represent a two-component vector.
struct vec2
{
    vec2();
    vec2(float x, float y);

    union
    {
        struct
        {
            float x;
            float y;
        };
        struct
        {
            float r;
            float g;
        };
    };

    float magnitude() const;
    void normalize();

    void add(const vec2 &other);
    void substract(const vec2 &other);
    void multiply(const vec2 &other);
    void multiply(const float &multiplier);
    void divide(const vec2 &other);
    void divide(const float &divider);

    bool isNull() const;

    void operator-();

    bool operator==(const vec2 &other) const;
    bool operator!=(const vec2 &other) const;
    bool operator<(const vec2 &other) const;
    bool operator<=(const vec2 &other) const;
    bool operator>(const vec2 &other) const;
    bool operator>=(const vec2 &other) const;

    vec2 operator+(const vec2 &other) const;
    vec2 operator-(const vec2 &other) const;
    vec2 operator*(const vec2 &other) const;
    vec2 operator*(const float &multiplier) const;
    vec2 operator/(const vec2 &other) const;
    vec2 operator/(const float &divider) const;
};

}
}
