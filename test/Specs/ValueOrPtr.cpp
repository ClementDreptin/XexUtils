#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void ValueOrPtr()
{
    Describe("ValueOrPtr");

    It("returns the value at the pointer when created with a pointer", []() {
        float value = 3.0f;
        XexUtils::ValueOrPtr<float> valueOrPtr(&value);

        TEST_EQ(valueOrPtr, value);
    });

    It("returns the value when created with a value", []() {
        float value = 3.0f;
        XexUtils::ValueOrPtr<float> valueOrPtr(value);

        TEST_EQ(valueOrPtr, value);
    });
}
