#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Vec4()
{
    Describe("Math::vec4");

    Math::vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    Math::vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    It("calculates the magnitude", [=]() {
        TEST_BETWEEN(v2.magnitude(), 13.19f, 13.20f);
    });

    It("normalizes itself", [=]() {
        Math::vec4 result = v2.normalize();

        TEST_BETWEEN(result.x, 0.37f, 0.38f);
        TEST_BETWEEN(result.y, 0.45f, 0.46f);
    });

    It("knows when it's null", [=]() {
        Math::vec4 null(0.0f, 0.0f, 0.0f, 0.0f);

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
        Math::vec4 result = v1 + v2;

        TEST_EQ(result.x, 6.0f);
        TEST_EQ(result.y, 8.0f);
        TEST_EQ(result.z, 10.0f);
        TEST_EQ(result.w, 12.0f);
    });

    It("performs substraction", [=]() {
        Math::vec4 result = v1 - v2;

        TEST_EQ(result.x, -4.0f);
        TEST_EQ(result.y, -4.0f);
        TEST_EQ(result.z, -4.0f);
        TEST_EQ(result.w, -4.0f);
    });

    It("performs multiplication with another vec4", [=]() {
        Math::vec4 result = v1 * v2;

        TEST_EQ(result.x, 5.0f);
        TEST_EQ(result.y, 12.0f);
        TEST_EQ(result.z, 21.0f);
        TEST_EQ(result.w, 32.0f);
    });

    It("performs multiplication with a float", [=]() {
        Math::vec4 result = v1 * 3.0f;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 6.0f);
        TEST_EQ(result.z, 9.0f);
        TEST_EQ(result.w, 12.0f);
    });

    It("performs division with another vec4", [=]() {
        Math::vec4 result = v2 / v1;

        TEST_EQ(result.x, 5.0f);
        TEST_EQ(result.y, 3.0f);
        TEST_BETWEEN(result.z, 2.33f, 2.34f);
        TEST_EQ(result.w, 2.0f);
    });

    It("performs division with a float", [=]() {
        Math::vec4 result = v2 / 2.0f;

        TEST_EQ(result.x, 2.5f);
        TEST_EQ(result.y, 3.0f);
        TEST_EQ(result.z, 3.5f);
        TEST_EQ(result.w, 4.0f);
    });

    It("performs the opposite", [=]() {
        Math::vec4 result = -v2;

        TEST_EQ(result.x, -5.0f);
        TEST_EQ(result.y, -6.0f);
        TEST_EQ(result.z, -7.0f);
        TEST_EQ(result.w, -8.0f);
    });
}
