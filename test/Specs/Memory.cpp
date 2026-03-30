#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Memory()
{
    Describe("Memory::Write");

    It("doesn't do anything when trying to write to an invalid address", []() {
        Memory::Write<float>(nullptr, 3.0f); // Just make sure we don't crash
    });

    It("writes to the given address when it's valid", []() {
        float value = 1.0f;
        Memory::Write<float>(&value, 2.0f);

        TEST_EQ(value, 2.0f);
    });

    Describe("Memory::Read");

    It("doesn't crash and returns the default value for the type when given an invalid address", []() {
        float value = Memory::Read<float>(nullptr);

        TEST_EQ(value, float());
    });

    It("reads the value at the given address when it's valid", []() {
        float value = 3.0f;

        TEST_EQ(Memory::Read<float>(&value), value);
    });
}
