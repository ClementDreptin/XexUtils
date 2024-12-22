#include "pch.h"
#include "specs.h"

#include "TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

static void Formatter()
{
    Describe("Formatter::Format");

    It("creates an std::string from a narrow format", []() {
        std::string result = Formatter::Format("hello %s %d", "world", 3);

        TEST_EQ(result, "hello world 3");
    });

    Describe("Formatter::WideFormat");

    It("creates and std::wstring from the wide format", []() {
        std::wstring result = Formatter::WideFormat(L"hello %s %d", L"world", 3);

        TEST_EQ(Formatter::ToNarrow(result), "hello world 3");
    });

    Describe("Formatter::ToWide");

    It("converts an std::string to an std::wstring", []() {
        std::string narrow = "hello";
        std::wstring wide = Formatter::ToWide(narrow);

        TEST_EQ(Formatter::ToNarrow(wide), "hello");
    });

    Describe("Formatter::ToNarrow");

    It("converts an std::wstring to an std::string", []() {
        std::wstring wide = L"hello";
        std::string narrow = Formatter::ToNarrow(wide);

        TEST_EQ(narrow, "hello");
    });
}

static void Vec2()
{
    Describe("vec2");

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

static void Vec3()
{
    Describe("vec3");

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

static void Vec4()
{
    Describe("vec4");

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

static void Math()
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

static void Memory()
{
    Describe("Memory::ResolveFunction");

    It("returns a valid pointer when given a valid module name and ordinal", []() {
        void *pFunc = Memory::ResolveFunction("xam.xex", 656); // XNotifyQueueUI

        TEST_NEQ(reinterpret_cast<uintptr_t>(pFunc), reinterpret_cast<uintptr_t>(nullptr));
    });

    It("returns nullptr when given an invalid module name", []() {
        void *pFunc = Memory::ResolveFunction("invalid.xex", 1);

        TEST_EQ(reinterpret_cast<uintptr_t>(pFunc), reinterpret_cast<uintptr_t>(nullptr));
    });

    It("returns nullptr when given an invalid ordinal", []() {
        void *pFunc = Memory::ResolveFunction("xam.xex", 0xFFFFFF);

        TEST_EQ(reinterpret_cast<uintptr_t>(pFunc), reinterpret_cast<uintptr_t>(nullptr));
    });

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

static void ValueOrPtr()
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

static void Xam()
{
    Describe("Xam::MountHdd");

    It("allows a game to access the hard drive", []() {
        std::ifstream file("hdd:\\launch.ini");
        TEST_EQ(file.is_open(), false);

        Xam::MountHdd();
        file.open("hdd:\\launch.ini");

        TEST_EQ(file.is_open(), true);
    });
}

void RunTests()
{
    ::Formatter();
    ::Vec2();
    ::Vec3();
    ::Vec4();
    ::Math();
    ::Memory();
    ::ValueOrPtr();
    ::Xam();

    TestRunner::Run();
}
