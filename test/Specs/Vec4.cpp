#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Vec4()
{
    Describe("Math::vec4()");

    It("creates an empty vec4", []() {
        auto v1 = Math::vec4();

        TEST_EQ(v1.x, 0.0f);
        TEST_EQ(v1.y, 0.0f);
        TEST_EQ(v1.z, 0.0f);
        TEST_EQ(v1.w, 0.0f);
    });

    Describe("Math::vec4(float, float, float, float)");

    It("creates a vec4 from x, y, z and w", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);

        TEST_EQ(v1.x, 1.0f);
        TEST_EQ(v1.y, 2.0f);
        TEST_EQ(v1.z, 3.0f);
        TEST_EQ(v1.w, 4.0f);
    });

    Describe("Math::vec4::magnitude()");

    It("calculates the magnitude", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        float magnitude = v1.magnitude();

        TEST_BETWEEN(magnitude, 13.19f, 13.20f);
    });

    Describe("Math::vec4::normalize()");

    It("normalizes the current vec4", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 result = v1.normalize();

        TEST_BETWEEN(result.x, 0.37f, 0.38f);
        TEST_BETWEEN(result.y, 0.45f, 0.46f);
        TEST_BETWEEN(result.z, 0.53f, 0.54f);
        TEST_BETWEEN(result.w, 0.60f, 0.61f);
    });

    Describe("Math::vec4::add(const Math::vec4 &)");

    It("adds the other vec4 to the current vec4", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);
        v1.add(v2);

        TEST_EQ(v1.x, 6.0f);
        TEST_EQ(v1.y, 8.0f);
        TEST_EQ(v1.z, 10.0f);
        TEST_EQ(v1.w, 12.0f);
    });

    Describe("Math::vec4::substract(const Math::vec4 &)");

    It("substracts the other vec4 from the current vec4", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);
        v1.substract(v2);

        TEST_EQ(v1.x, 4.0f);
        TEST_EQ(v1.y, 4.0f);
        TEST_EQ(v1.z, 4.0f);
        TEST_EQ(v1.w, 4.0f);
    });

    Describe("Math::vec4::multiply(const Math::vec4 &)");

    It("multiplies the current vec4 by the other vec4", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);
        v1.multiply(v2);

        TEST_EQ(v1.x, 5.0f);
        TEST_EQ(v1.y, 12.0f);
        TEST_EQ(v1.z, 21.0f);
        TEST_EQ(v1.w, 32.0f);
    });

    Describe("Math::vec4::multiply(const float &)");

    It("multiplies the current vec4 by the multiplier", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        float multiplier = 2.0f;
        v1.multiply(multiplier);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 4.0f);
        TEST_EQ(v1.z, 6.0f);
        TEST_EQ(v1.w, 8.0f);
    });

    Describe("Math::vec4::divide(const Math::vec4 &)");

    It("divides the current vec4 by the other vec4", []() {
        Math::vec4 v1(4.0f, 6.0f, 8.0f, 10.0f);
        Math::vec4 v2(2.0f, 3.0f, 4.0f, 5.0f);
        v1.divide(v2);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 2.0f);
        TEST_EQ(v1.z, 2.0f);
        TEST_EQ(v1.w, 2.0f);
    });

    Describe("Math::vec4::divide(const float &)");

    It("divides the current vec4 by the divider", []() {
        Math::vec4 v1(4.0f, 6.0f, 8.0f, 10.0f);
        float divider = 2.0f;
        v1.divide(divider);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 3.0f);
        TEST_EQ(v1.z, 4.0f);
        TEST_EQ(v1.w, 5.0f);
    });

    Describe("Math::vec4::isNull()");

    It("returns true when the vec4 is null", []() {
        Math::vec4 v1(0.0f, 0.0f, 0.0f, 0.0f);

        TEST_EQ(v1.isNull(), true);
    });

    It("returns false when the vec4 is not null", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);

        TEST_EQ(v1.isNull(), false);
    });

    Describe("Math::vec4::operator==(const vec4 &)");

    It("returns true when the vec4s are equal", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);

        TEST_EQ(v1 == v2, true);
    });

    It("returns false when the vec4s are not equal", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

        TEST_EQ(v1 == v2, false);
    });

    Describe("Math::vec4::operator!=(const vec4 &)");

    It("returns true when the vec4s not are equal", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

        TEST_EQ(v1 != v2, true);
    });

    It("returns false when the vec4s are equal", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);

        TEST_EQ(v1 != v2, false);
    });

    Describe("Math::vec4::operator<(const vec4 &)");

    It("returns true when v1 is less than v2", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

        TEST_EQ(v1 < v2, true);
    });

    It("returns false when v1 is greater than v2", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);

        TEST_EQ(v1 < v2, false);
    });

    Describe("Math::vec4::operator<=(const vec4 &)");

    It("returns true when v1 is less than or equal to v2", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

        TEST_EQ(v1 <= v2, true);
        TEST_EQ(v1 <= v1, true);
    });

    It("returns false when v1 is greater than v2", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);

        TEST_EQ(v1 <= v2, false);
    });

    Describe("Math::vec4::operator>(const vec4 &)");

    It("returns true when v1 is greater than v2", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);

        TEST_EQ(v1 > v2, true);
    });

    It("returns false when v1 is less than v2", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

        TEST_EQ(v1 > v2, false);
    });

    Describe("Math::vec4::operator>=(const vec4 &)");

    It("returns true when v1 is greater than or equal to v2", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);

        TEST_EQ(v1 >= v2, true);
        TEST_EQ(v1 >= v1, true);
    });

    It("returns false when v1 is less than v2", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

        TEST_EQ(v1 >= v2, false);
    });

    Describe("Math::vec4::operator+(const vec4 &)");

    It("adds v1 to v2", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 result = v1 + v2;

        TEST_EQ(result.x, 6.0f);
        TEST_EQ(result.y, 8.0f);
        TEST_EQ(result.z, 10.0f);
        TEST_EQ(result.w, 12.0f);
    });

    Describe("Math::vec4::operator-(const vec4 &)");

    It("substracts v2 from v1", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 result = v1 - v2;

        TEST_EQ(result.x, 4.0f);
        TEST_EQ(result.y, 4.0f);
        TEST_EQ(result.z, 4.0f);
        TEST_EQ(result.w, 4.0f);
    });

    Describe("Math::vec4::operator*(const vec4 &)");

    It("multiplies v1 with v2", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 result = v1 * v2;

        TEST_EQ(result.x, 5.0f);
        TEST_EQ(result.y, 12.0f);
        TEST_EQ(result.z, 21.0f);
        TEST_EQ(result.w, 32.0f);
    });

    Describe("Math::vec4::operator*(const float &)");

    It("multiplies v1 with a float", []() {
        Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 result = v1 * 3.0f;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 6.0f);
        TEST_EQ(result.z, 9.0f);
        TEST_EQ(result.w, 12.0f);
    });

    Describe("Math::vec4::operator/(const vec4 &)");

    It("divides v1 by v2", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);
        Math::vec4 result = v1 / v2;

        TEST_EQ(result.x, 5.0f);
        TEST_EQ(result.y, 3.0f);
        TEST_BETWEEN(result.z, 2.33f, 2.34f);
        TEST_EQ(result.w, 2.0f);
    });

    Describe("Math::vec4::operator/(const float &)");

    It("divides v1 by a float", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 result = v1 / 2.0f;

        TEST_EQ(result.x, 2.5f);
        TEST_EQ(result.y, 3.0f);
        TEST_EQ(result.z, 3.5f);
        TEST_EQ(result.w, 4.0f);
    });

    Describe("Math::vec4::operator-()");

    It("returns the opposite", []() {
        Math::vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
        Math::vec4 result = -v1;

        TEST_EQ(result.x, -5.0f);
        TEST_EQ(result.y, -6.0f);
        TEST_EQ(result.z, -7.0f);
        TEST_EQ(result.w, -8.0f);
    });
}
