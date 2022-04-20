# Math

Adding two three-component vectors together (check the [vec2](../include/Vec2.h), [vec3](../include/Vec3.h) and [vec4](../include/Vec4.h) structs to see all the available operations):
```C++
void Init()
{
    XexUtils::Math::vec3 Vec1(1.0f, 2.0f, 3.0f);
    XexUtils::Math::vec3 Vec2(2.0f, 3.0f, 4.0f);

    XexUtils::Math::vec3 Vec3 = Vec1 + Vec2; // x: 3.0, y: 5.0, z: 7.0
}
```

Converting an angle from degrees to radians:
```C++
void Init()
{
    double dbDegrees = 30;
    double dbRadians = XexUtils::Math::Radians(dbDegrees); // 0.523599
}
```

Projecting a vector:
```C++
void Init()
{
    XexUtils::Math::vec3 MyCurrentPosition = GetCurrentPosition();
    XexUtils::Math::vec3 MyCurrentOrientation = GetCurrentOrientation();
    XexUtils::Math::vec3 TenUnitsInFrontOfMe = XexUtils::Math::ToFront(MyCurrentPosition, MyCurrentOrientation.y, 10);
}
```
