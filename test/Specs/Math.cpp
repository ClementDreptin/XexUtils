#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Math()
{
    Describe("Math::Radians");

    It("converts degrees to radians", []() {
        TEST_BETWEEN(Math::Radians(45.0f), 0.78f, 0.79f);
    });

    Describe("Math::ProjectForward");

    It("projects a vector based on an orientation", []() {
        Math::vec3 v1(1.0f, 2.0f, 3.0f);
        Math::vec3 v2 = Math::ProjectForward(v1, 45.0f, 10.0f);

        TEST_BETWEEN(v2.x, 6.25f, 6.26f);
        TEST_BETWEEN(v2.y, 10.50f, 10.51f);
        TEST_EQ(v2.z, 3.0f);
    });

    Describe("Math::RoundToNextMultiple");

    It("rounds to the next multiple", []() {
        TEST_EQ(Math::RoundToNextMultipleOf<3>(4), 6);
        TEST_EQ(Math::RoundToNextMultipleOf<5>(2), 5);
        TEST_EQ(Math::RoundToNextMultipleOf<4>(4), 8);
    });
}
