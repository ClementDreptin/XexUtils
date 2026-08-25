#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Vec3()
{
    Describe("Math::vec3()");

    It("creates an empty vec3", []() {
        auto v1 = Math::vec3();

        TEST_EQ(v1.x, 0.0f);
        TEST_EQ(v1.y, 0.0f);
        TEST_EQ(v1.z, 0.0f);
    });

    Describe("Math::vec3(float, float, float)");

    It("creates a vec3 from x, y and z", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);

        TEST_EQ(v1.x, 1.0f);
        TEST_EQ(v1.y, 2.0f);
        TEST_EQ(v1.z, 3.0f);
    });

    Describe("Math::vec3::magnitude()");

    It("calculates the magnitude", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        float magnitude = v1.magnitude();

        TEST_BETWEEN(magnitude, 8.77f, 8.78f);
    });

    Describe("Math::vec3::normalize()");

    It("normalizes the current vec3", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 result = v1.normalize();

        TEST_BETWEEN(result.x, 0.45f, 0.46f);
        TEST_BETWEEN(result.y, 0.56f, 0.57f);
        TEST_BETWEEN(result.z, 0.68f, 0.69f);
    });

    Describe("Math::vec3::add(const Math::vec3 &)");

    It("adds the other vec3 to the current vec3", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);
        v1.add(v2);

        TEST_EQ(v1.x, 5.0f);
        TEST_EQ(v1.y, 7.0f);
        TEST_EQ(v1.z, 9.0f);
    });

    Describe("Math::vec3::substract(const Math::vec3 &)");

    It("substracts the other vec3 from the current vec3", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);
        v1.substract(v2);

        TEST_EQ(v1.x, 3.0f);
        TEST_EQ(v1.y, 3.0f);
        TEST_EQ(v1.z, 3.0f);
    });

    Describe("Math::vec3::multiply(const Math::vec3 &)");

    It("multiplies the current vec3 by the other vec3", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);
        v1.multiply(v2);

        TEST_EQ(v1.x, 4.0f);
        TEST_EQ(v1.y, 10.0f);
        TEST_EQ(v1.z, 18.0f);
    });

    Describe("Math::vec3::multiply(const float &)");

    It("multiplies the current vec3 by the multiplier", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        float multiplier = 2.0f;
        v1.multiply(multiplier);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 4.0f);
        TEST_EQ(v1.z, 6.0f);
    });

    Describe("Math::vec3::divide(const Math::vec3 &)");

    It("divides the current vec3 by the other vec3", []() {
        Math::vec3 v1(4.0f, 6.0f, 8.0f);
        Math::vec3 v2(2.0f, 3.0f, 4.0f);
        v1.divide(v2);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 2.0f);
        TEST_EQ(v1.z, 2.0f);
    });

    Describe("Math::vec3::divide(const float &)");

    It("divides the current vec3 by the divider", []() {
        Math::vec3 v1(4.0f, 6.0f, 8.0f);
        float divider = 2.0f;
        v1.divide(divider);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 3.0f);
        TEST_EQ(v1.z, 4.0f);
    });

    Describe("Math::vec3::isNull()");

    It("returns true when the vec3 is null", []() {
        Math::vec3 v1(0.0f, 0.0f, 0.0f);

        TEST_EQ(v1.isNull(), true);
    });

    It("returns false when the vec3 is not null", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);

        TEST_EQ(v1.isNull(), false);
    });

    Describe("Math::vec3::operator==(const vec3 &)");

    It("returns true when the vec3s are equal", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);

        TEST_EQ(v1 == v2, true);
    });

    It("returns false when the vec3s are not equal", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);

        TEST_EQ(v1 == v2, false);
    });

    Describe("Math::vec3::operator!=(const vec3 &)");

    It("returns true when the vec3s not are equal", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);

        TEST_EQ(v1 != v2, true);
    });

    It("returns false when the vec3s are equal", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);

        TEST_EQ(v1 != v2, false);
    });

    Describe("Math::vec3::operator<(const vec3 &)");

    It("returns true when v1 is less than v2", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);

        TEST_EQ(v1 < v2, true);
    });

    It("returns false when v1 is greater than v2", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);

        TEST_EQ(v1 < v2, false);
    });

    Describe("Math::vec3::operator<=(const vec3 &)");

    It("returns true when v1 is less than or equal to v2", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);

        TEST_EQ(v1 <= v2, true);
        TEST_EQ(v1 <= v1, true);
    });

    It("returns false when v1 is greater than v2", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);

        TEST_EQ(v1 <= v2, false);
    });

    Describe("Math::vec3::operator>(const vec3 &)");

    It("returns true when v1 is greater than v2", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);

        TEST_EQ(v1 > v2, true);
    });

    It("returns false when v1 is less than v2", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);

        TEST_EQ(v1 > v2, false);
    });

    Describe("Math::vec3::operator>=(const vec3 &)");

    It("returns true when v1 is greater than or equal to v2", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);

        TEST_EQ(v1 >= v2, true);
        TEST_EQ(v1 >= v1, true);
    });

    It("returns false when v1 is less than v2", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);

        TEST_EQ(v1 >= v2, false);
    });

    Describe("Math::vec3::operator+(const vec3 &)");

    It("adds v1 to v2", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);
        Math::vec3 result = v1 + v2;

        TEST_EQ(result.x, 5.0f);
        TEST_EQ(result.y, 7.0f);
        TEST_EQ(result.z, 9.0f);
    });

    Describe("Math::vec3::operator-(const vec3 &)");

    It("substracts v2 from v1", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);
        Math::vec3 result = v1 - v2;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 3.0f);
        TEST_EQ(result.z, 3.0f);
    });

    Describe("Math::vec3::operator*(const vec3 &)");

    It("multiplies v1 with v2", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2(4.0f, 5.0f, 6.0f);
        Math::vec3 result = v1 * v2;

        TEST_EQ(result.x, 4.0f);
        TEST_EQ(result.y, 10.0f);
        TEST_EQ(result.z, 18.0f);
    });

    Describe("Math::vec3::operator*(const float &)");

    It("multiplies v1 with a float", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 result = v1 * 3.0f;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 6.0f);
        TEST_EQ(result.z, 9.0f);
    });

    Describe("Math::vec3::operator/(const vec3 &)");

    It("divides v1 by v2", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 v2(1.0f, 2.0f, 3.0f);
        Math::vec3 result = v1 / v2;

        TEST_EQ(result.x, 4.0f);
        TEST_EQ(result.y, 2.5f);
        TEST_EQ(result.z, 2.0f);
    });

    Describe("Math::vec3::operator/(const float &)");

    It("divides v1 by a float", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 result = v1 / 2.0f;

        TEST_EQ(result.x, 2.0f);
        TEST_EQ(result.y, 2.5f);
        TEST_EQ(result.z, 3.0f);
    });

    Describe("Math::vec3::operator-()");

    It("returns the opposite", []() {
        Math::vec3 v1(4.0f, 5.0f, 6.0f);
        Math::vec3 result = -v1;

        TEST_EQ(result.x, -4.0f);
        TEST_EQ(result.y, -5.0f);
        TEST_EQ(result.z, -6.0f);
    });
}
