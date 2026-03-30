#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Vec3()
{
    Describe("Math::vec3");

    Math::vec3 v1(1.0f, 2.0f, 3.0f);
    Math::vec3 v2(4.0f, 5.0f, 6.0f);

    It("calculates the magnitude", [=]() {
        TEST_BETWEEN(v2.magnitude(), 8.77f, 8.78f);
    });

    It("normalizes itself", [=]() {
        Math::vec3 result = v2.normalize();

        TEST_BETWEEN(result.x, 0.45f, 0.46f);
        TEST_BETWEEN(result.y, 0.56f, 0.57f);
    });

    It("knows when it's null", [=]() {
        Math::vec3 null(0.0f, 0.0f, 0.0f);

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
        Math::vec3 result = v1 + v2;

        TEST_EQ(result.x, 5.0f);
        TEST_EQ(result.y, 7.0f);
        TEST_EQ(result.z, 9.0f);
    });

    It("performs substraction", [=]() {
        Math::vec3 result = v1 - v2;

        TEST_EQ(result.x, -3.0f);
        TEST_EQ(result.y, -3.0f);
        TEST_EQ(result.z, -3.0f);
    });

    It("performs multiplication with another vec3", [=]() {
        Math::vec3 result = v1 * v2;

        TEST_EQ(result.x, 4.0f);
        TEST_EQ(result.y, 10.0f);
        TEST_EQ(result.z, 18.0f);
    });

    It("performs multiplication with a float", [=]() {
        Math::vec3 result = v1 * 3.0f;

        TEST_EQ(result.x, 3.0f);
        TEST_EQ(result.y, 6.0f);
        TEST_EQ(result.z, 9.0f);
    });

    It("performs division with another vec3", [=]() {
        Math::vec3 result = v2 / v1;

        TEST_EQ(result.x, 4.0f);
        TEST_EQ(result.y, 2.5f);
        TEST_EQ(result.z, 2.0f);
    });

    It("performs division with a float", [=]() {
        Math::vec3 result = v2 / 2.0f;

        TEST_EQ(result.x, 2.0f);
        TEST_EQ(result.y, 2.5f);
        TEST_EQ(result.z, 3.0f);
    });

    It("performs the opposite", [=]() {
        Math::vec3 result = -v2;

        TEST_EQ(result.x, -4.0f);
        TEST_EQ(result.y, -5.0f);
        TEST_EQ(result.z, -6.0f);
    });
}
