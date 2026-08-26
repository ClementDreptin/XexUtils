#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Vec2()
{
    Describe("Math::vec2::vec2()");

    It("creates an empty vec2", []() {
        auto v1 = Math::vec2();

        TEST_EQ(v1.x, 0.0f);
        TEST_EQ(v1.y, 0.0f);
    });

    Describe("Math::vec2::vec2(float, float)");

    It("creates a vec2 from x and y", []() {
        Math::vec2 v1(1.0f, 2.0f);

        TEST_EQ(v1.x, 1.0f);
        TEST_EQ(v1.y, 2.0f);
    });

    Describe("Math::vec2::magnitude()");

    It("calculates the magnitude", []() {
        Math::vec2 v1(3.0f, 4.0f);
        float magnitude = v1.magnitude();

        TEST_EQ(magnitude, 5);
    });

    Describe("Math::vec2::normalize()");

    It("normalizes the current vec2", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 result = v1.normalize();

        TEST_EQ(result.x, 0.6f);
        TEST_EQ(result.y, 0.8f);
    });

    Describe("Math::vec2::add(const Math::vec2 &)");

    It("adds the other vec2 to the current vec2", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);
        v1.add(v2);

        TEST_EQ(v1.x, 4.0f);
        TEST_EQ(v1.y, 6.0f);
    });

    Describe("Math::vec2::substract(const Math::vec2 &)");

    It("substracts the other vec2 from the current vec2", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 v2(1.0f, 2.0f);
        v1.substract(v2);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 2.0f);
    });

    Describe("Math::vec2::multiply(const Math::vec2 &)");

    It("multiplies the current vec2 by the other vec2", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);
        v1.multiply(v2);

        TEST_EQ(v1.x, 3.0f);
        TEST_EQ(v1.y, 8.0f);
    });

    Describe("Math::vec2::multiply(const float &)");

    It("multiplies the current vec2 by the multiplier", []() {
        Math::vec2 v1(1.0f, 2.0f);
        float multiplier = 2.0f;
        v1.multiply(multiplier);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 4.0f);
    });

    Describe("Math::vec2::divide(const Math::vec2 &)");

    It("divides the current vec2 by the other vec2", []() {
        Math::vec2 v1(4.0f, 6.0f);
        Math::vec2 v2(2.0f, 3.0f);
        v1.divide(v2);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 2.0f);
    });

    Describe("Math::vec2::divide(const float &)");

    It("divides the current vec2 by the divider", []() {
        Math::vec2 v1(4.0f, 6.0f);
        float divider = 2.0f;
        v1.divide(divider);

        TEST_EQ(v1.x, 2.0f);
        TEST_EQ(v1.y, 3.0f);
    });

    Describe("Math::vec2::isNull()");

    It("returns true when the vec2 is null", []() {
        Math::vec2 v1(0.0f, 0.0f);

        TEST_EQ(v1.isNull(), true);
    });

    It("returns false when the vec2 is not null", []() {
        Math::vec2 v1(1.0f, 2.0f);

        TEST_EQ(v1.isNull(), false);
    });

    Describe("Math::vec2::operator==(const vec2 &)");

    It("returns true when the vec2s are equal", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(1.0f, 2.0f);

        TEST_EQ(v1 == v2, true);
    });

    It("returns false when the vec2s are not equal", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);

        TEST_EQ(v1 == v2, false);
    });

    Describe("Math::vec2::operator!=(const vec2 &)");

    It("returns true when the vec2s not are equal", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);

        TEST_EQ(v1 != v2, true);
    });

    It("returns false when the vec2s are equal", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(1.0f, 2.0f);

        TEST_EQ(v1 != v2, false);
    });

    Describe("Math::vec2::operator<(const vec2 &)");

    It("returns true when v1 is less than v2", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);

        TEST_EQ(v1 < v2, true);
    });

    It("returns false when v1 is greater than v2", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 v2(1.0f, 2.0f);

        TEST_EQ(v1 < v2, false);
    });

    Describe("Math::vec2::operator<=(const vec2 &)");

    It("returns true when v1 is less than or equal to v2", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);

        TEST_EQ(v1 <= v2, true);
        TEST_EQ(v1 <= v1, true);
    });

    It("returns false when v1 is greater than v2", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 v2(1.0f, 2.0f);

        TEST_EQ(v1 <= v2, false);
    });

    Describe("Math::vec2::operator>(const vec2 &)");

    It("returns true when v1 is greater than v2", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 v2(1.0f, 2.0f);

        TEST_EQ(v1 > v2, true);
    });

    It("returns false when v1 is less than v2", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);

        TEST_EQ(v1 > v2, false);
    });

    Describe("Math::vec2::operator>=(const vec2 &)");

    It("returns true when v1 is greater than or equal to v2", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 v2(1.0f, 2.0f);

        TEST_EQ(v1 >= v2, true);
        TEST_EQ(v1 >= v1, true);
    });

    It("returns false when v1 is less than v2", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);

        TEST_EQ(v1 >= v2, false);
    });

    Describe("Math::vec2::operator+(const vec2 &)");

    It("adds v1 to v2", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);
        Math::vec2 result = v1 + v2;

        TEST_EQ(result.x, 4.0f);
        TEST_EQ(result.y, 6.0f);
    });

    Describe("Math::vec2::operator-(const vec2 &)");

    It("substracts v2 from v1", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 v2(1.0f, 2.0f);
        Math::vec2 result = v1 - v2;

        TEST_EQ(result.x, 2.0f);
        TEST_EQ(result.y, 2.0f);
    });

    Describe("Math::vec2::operator*(const vec2 &)");

    It("multiplies v1 with v2", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 v2(3.0f, 4.0f);
        Math::vec2 result = v1 * v2;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 8.0f);
    });

    Describe("Math::vec2::operator*(const float &)");

    It("multiplies v1 with a float", []() {
        Math::vec2 v1(1.0f, 2.0f);
        Math::vec2 result = v1 * 3.0f;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 6.0f);
    });

    Describe("Math::vec2::operator/(const vec2 &)");

    It("divides v1 by v2", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 v2(1.0f, 2.0f);
        Math::vec2 result = v1 / v2;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 2.0f);
    });

    Describe("Math::vec2::operator/(const float &)");

    It("divides v1 by a float", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 result = v1 / 2.0f;

        TEST_EQ(result.x, 1.5f);
        TEST_EQ(result.y, 2.0f);
    });

    Describe("Math::vec2::operator-()");

    It("returns the opposite", []() {
        Math::vec2 v1(3.0f, 4.0f);
        Math::vec2 result = -v1;

        TEST_EQ(result.x, -3.0f);
        TEST_EQ(result.y, -4.0f);
    });
}
