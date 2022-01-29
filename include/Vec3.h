#pragma once


namespace XexUtils
{
namespace Math
{

// Struct to represent a three-component vector.
struct vec3
{
    vec3();
    vec3(float x, float y, float z);

    float x;
    float y;
    float z;

    float magnitude() const;
    void normalize();

    void add(const vec3 &other);
    void substract(const vec3 &other);
    void multiply(const vec3 &other);
    void multiply(const float &multiplier);
    void divide(const vec3 &other);
    void divide(const float &divider);

    bool isNull() const;

    void operator-();

    bool operator==(const vec3 &other) const;
    bool operator!=(const vec3 &other) const;
    bool operator<(const vec3 &other) const;
    bool operator<=(const vec3 &other) const;
    bool operator>(const vec3 &other) const;
    bool operator>=(const vec3 &other) const;

    vec3 operator+(const vec3 &other) const;
    vec3 operator-(const vec3 &other) const;
    vec3 operator*(const vec3 &other) const;
    vec3 operator*(const float &multiplier) const;
    vec3 operator/(const vec3 &other) const;
    vec3 operator/(const float &divider) const;
};

}
}
