#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Vec2()
{
    Describe("Math::vec2");

    Math::vec2 v1(1.0f, 2.0f);
    Math::vec2 v2(3.0f, 4.0f);

    It("calculates the magnitude", [=]() {
        float magnitude = v2.magnitude();

        TEST_EQ(magnitude, 5);
    });

    It("normalizes itself", [=]() {
        Math::vec2 result = v2.normalize();

        TEST_EQ(result.x, 0.6f);
        TEST_EQ(result.y, 0.8f);
    });

    It("knows when it's null", [=]() {
        Math::vec2 null(0.0f, 0.0f);

        TEST_EQ(null.isNull(), true);
        TEST_EQ(v2.isNull(), false);
    });

    It("performs equality", [=]() {
        TEST_EQ(v1 == v1, true);
        TEST_EQ(v1 == v2, false);
    });

    It("performs inequality", [=]() {
        TEST_EQ(v1 != v1, false);
        TEST_EQ(v1 != v2, true);
    });

    It("performs less than", [=]() {
        TEST_EQ(v1 < v2, true);
        TEST_EQ(v2 < v1, false);
    });

    It("performs less than or equal to", [=]() {
        TEST_EQ(v1 <= v2, true);
        TEST_EQ(v1 <= v1, true);
        TEST_EQ(v2 <= v1, false);
    });

    It("performs greater than", [=]() {
        TEST_EQ(v1 > v2, false);
        TEST_EQ(v2 > v1, true);
    });

    It("performs greater than or equal to", [=]() {
        TEST_EQ(v1 >= v2, false);
        TEST_EQ(v1 >= v1, true);
        TEST_EQ(v2 >= v1, true);
    });

    It("performs addition", [=]() {
        Math::vec2 result = v1 + v2;

        TEST_EQ(result.x, 4.0f);
        TEST_EQ(result.y, 6.0f);
    });

    It("performs substraction", [=]() {
        Math::vec2 result = v1 - v2;

        TEST_EQ(result.x, -2.0f);
        TEST_EQ(result.y, -2.0f);
    });

    It("performs multiplication with another vec2", [=]() {
        Math::vec2 result = v1 * v2;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 8.0f);
    });

    It("performs multiplication with a float", [=]() {
        Math::vec2 result = v1 * 3.0f;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 6.0f);
    });

    It("performs division with another vec2", [=]() {
        Math::vec2 result = v2 / v1;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 2.0f);
    });

    It("performs division with a float", [=]() {
        Math::vec2 result = v2 / 2.0f;

        TEST_EQ(result.x, 1.5f);
        TEST_EQ(result.y, 2.0f);
    });

    It("performs the opposite", [=]() {
        Math::vec2 result = -v2;

        TEST_EQ(result.x, -3.0f);
        TEST_EQ(result.y, -4.0f);
    });
}
