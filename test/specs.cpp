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

    Describe("Formatter::Format (wide)");

    It("creates and std::wstring from the wide format", []() {
        std::wstring result = Formatter::Format(L"hello %s %d", L"world", 3);

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

static void Path()
{
    Describe("Path");

    It("concatenates an std::string with a path", []() {
        XexUtils::Path path("File.txt");
        XexUtils::Path newPath = "C:\\Windows\\System32" + path;

        TEST_EQ(newPath.Drive(), "C:");
        TEST_EQ(newPath.Basename(), "System32File");
        TEST_EQ(newPath.Extension(), ".txt");
        TEST_EQ(newPath.Filename(), "System32File.txt");
        TEST_EQ(newPath.Parent(), "C:\\Windows");
        TEST_EQ(newPath.RelativePath(), "\\Windows\\System32File.txt");
        TEST_EQ(newPath.IsRoot(), false);
        TEST_EQ(newPath.String(), "C:\\Windows\\System32File.txt");
    });

    It("concatenates a path with an std::string", []() {
        XexUtils::Path path("C:\\Windows\\System32");
        XexUtils::Path newPath = path + "File.txt";

        TEST_EQ(newPath.Drive(), "C:");
        TEST_EQ(newPath.Basename(), "System32File");
        TEST_EQ(newPath.Extension(), ".txt");
        TEST_EQ(newPath.Filename(), "System32File.txt");
        TEST_EQ(newPath.Parent(), "C:\\Windows");
        TEST_EQ(newPath.RelativePath(), "\\Windows\\System32File.txt");
        TEST_EQ(newPath.IsRoot(), false);
        TEST_EQ(newPath.String(), "C:\\Windows\\System32File.txt");
    });

    It("appends a path with a leading separator to a path without a trailing separator", []() {
        XexUtils::Path path("C:\\Windows\\System32");
        path /= "\\Documents\\File.txt";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    It("appends a path without a leading separator to a path without a trailing separator", []() {
        XexUtils::Path path("C:\\Windows\\System32");
        path /= "Documents\\File.txt";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    It("appends a path with a leading separator to a path with a trailing separator", []() {
        XexUtils::Path path("C:\\Windows\\System32\\");
        path /= "\\Documents\\File.txt";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    It("appends a path without a leading separator to a path with a trailing separator", []() {
        XexUtils::Path path("C:\\Windows\\System32\\");
        path /= "Documents\\File.txt";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    It("appends an empty path to a path without a trailing separator", []() {
        XexUtils::Path path("C:\\Windows\\System32");
        path /= "";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "");
        TEST_EQ(path.Extension(), "");
        TEST_EQ(path.Filename(), "");
        TEST_EQ(path.Parent(), "C:\\Windows");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\");
    });

    It("appends an empty path to a path with a trailing separator", []() {
        XexUtils::Path path("C:\\Windows\\System32\\");
        path /= "";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "");
        TEST_EQ(path.Extension(), "");
        TEST_EQ(path.Filename(), "");
        TEST_EQ(path.Parent(), "C:\\Windows");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\");
    });

    It("appends a path without a leading separator to an empty path", []() {
        XexUtils::Path path("");
        path /= "Documents\\File.txt";

        TEST_EQ(path.Drive(), "");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "\\Documents");
        TEST_EQ(path.RelativePath(), "\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "\\Documents\\File.txt");
    });

    It("appends a path with a leading separator to an empty path", []() {
        XexUtils::Path path("");
        path /= "\\Documents\\File.txt";

        TEST_EQ(path.Drive(), "");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "\\Documents");
        TEST_EQ(path.RelativePath(), "\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "\\Documents\\File.txt");
    });

    It("checks equality on two paths", []() {
        XexUtils::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        XexUtils::Path path2("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path1 == path2, true);
    });

    It("checks equality on an std::string and a path", []() {
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");
        XexUtils::Path path1("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(str1 == path1, true);
    });

    It("checks equality on a path and an std::string", []() {
        XexUtils::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path1 == str1, true);
    });

    It("checks inequality on two paths", []() {
        XexUtils::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        XexUtils::Path path2("Documents\\File.txt");

        TEST_EQ(path1 != path2, true);
    });

    It("checks inequality on an std::string and a path", []() {
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");
        XexUtils::Path path1("Documents\\File.txt");

        TEST_EQ(str1 != path1, true);
    });

    It("checks inequality on a path and an std::string", []() {
        XexUtils::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        std::string str1("Documents\\File.txt");

        TEST_EQ(path1 != str1, true);
    });

    It("extracts the drive from a path with a drive and a relative path", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Drive(), "C:");
    });

    It("extract the drive from a path with just a drive", []() {
        XexUtils::Path path("C:");

        TEST_EQ(path.Drive(), "C:");
    });

    It("returns an empty path when extracting the drive from a path without a drive", []() {
        XexUtils::Path path("\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Drive(), "");
    });

    It("extracts the basename of a complete path", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Basename(), "File");
    });

    It("extracts the basename of a path with just a file", []() {
        XexUtils::Path path("File.txt");

        TEST_EQ(path.Basename(), "File");
    });

    It("returns an empty path when extracting the basename of a path with just a drive", []() {
        XexUtils::Path path("C:");

        TEST_EQ(path.Basename(), "");
    });

    It("extracts the basename of a path with a file starting with a dot", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\.gitignore");

        TEST_EQ(path.Basename(), ".gitignore");
    });

    It("extracts the extension of a complete path", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Extension(), ".txt");
    });

    It("returns an empty path when extracting the extension of a file with no dot", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\File");

        TEST_EQ(path.Extension(), "");
    });

    It("returns an empty path when extracting the extension of a file starting with a dot", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\.gitignore");

        TEST_EQ(path.Extension(), "");
    });

    It("extracts the file name of a complete path", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Filename(), "File.txt");
    });

    It("extracts the parent of a complete path", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
    });

    It("returns an empty path when extracting the parent of an empty path", []() {
        XexUtils::Path path("");

        TEST_EQ(path.Parent(), "");
    });

    It("returns the current path when extracting the parent of a root path", []() {
        XexUtils::Path path("C:\\");

        TEST_EQ(path.Parent(), "C:\\");
    });

    It("extracts the parent of a path with a trailing separator", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\");

        TEST_EQ(path.Parent(), "C:\\Windows\\System32");
    });

    It("extracts the parent of a path with a leading separator", []() {
        XexUtils::Path path("\\File.txt");

        TEST_EQ(path.Parent(), "\\");
    });

    It("extracts the parent of a path with a drive and no separators", []() {
        XexUtils::Path path("C:File.txt");

        TEST_EQ(path.Parent(), "C:");
    });

    It("returns an empty path when extracting the parent of a parent with no separators", []() {
        XexUtils::Path path("File.txt");

        TEST_EQ(path.Parent(), "");
    });

    It("extracts the relative path of a complete path", []() {
        XexUtils::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
    });

    It("returns an empty path when extracting the relative path of a path with just a drive", []() {
        XexUtils::Path path("C:");

        TEST_EQ(path.RelativePath(), "");
    });

    It("returns the current path when extracting the relative path of a path without a drive", []() {
        XexUtils::Path path("\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
    });

    // IsRoot
    It("considers a path with just a drive and a separator to be root", []() {
        XexUtils::Path path("C:\\");

        TEST_EQ(path.IsRoot(), true);
    });

    It("considers a path with just a drive to be root", []() {
        XexUtils::Path path("C:");

        TEST_EQ(path.IsRoot(), true);
    });

    It("doesn't consider a path with a drive and a file name to be root", []() {
        XexUtils::Path path("C:\\File.txt");

        TEST_EQ(path.IsRoot(), false);
    });

    It("doesn't consider a path with a file name to be root", []() {
        XexUtils::Path path("File.txt");

        TEST_EQ(path.IsRoot(), false);
    });

    It("considers an empty path to be root", []() {
        XexUtils::Path path("");

        TEST_EQ(path.IsRoot(), true);
    });

    It("considers a path with just a separator to be root", []() {
        XexUtils::Path path("\\");

        TEST_EQ(path.IsRoot(), true);
    });

    It("doesn't consider a path to a directory to be root", []() {
        XexUtils::Path path("\\Documents\\");

        TEST_EQ(path.IsRoot(), false);
    });
}

static void Socket()
{
    Describe("Socket");

    const std::array<uint8_t, 73> EC_DN = {
        0x30, 0x47, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
        0x02, 0x55, 0x53, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 0x04, 0x0A,
        0x13, 0x19, 0x47, 0x6F, 0x6F, 0x67, 0x6C, 0x65, 0x20, 0x54, 0x72, 0x75,
        0x73, 0x74, 0x20, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x20,
        0x4C, 0x4C, 0x43, 0x31, 0x14, 0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x03,
        0x13, 0x0B, 0x47, 0x54, 0x53, 0x20, 0x52, 0x6F, 0x6F, 0x74, 0x20, 0x52,
        0x34
    };

    const std::array<uint8_t, 97> EC_Q = {
        0x04, 0xF3, 0x74, 0x73, 0xA7, 0x68, 0x8B, 0x60, 0xAE, 0x43, 0xB8, 0x35,
        0xC5, 0x81, 0x30, 0x7B, 0x4B, 0x49, 0x9D, 0xFB, 0xC1, 0x61, 0xCE, 0xE6,
        0xDE, 0x46, 0xBD, 0x6B, 0xD5, 0x61, 0x18, 0x35, 0xAE, 0x40, 0xDD, 0x73,
        0xF7, 0x89, 0x91, 0x30, 0x5A, 0xEB, 0x3C, 0xEE, 0x85, 0x7C, 0xA2, 0x40,
        0x76, 0x3B, 0xA9, 0xC6, 0xB8, 0x47, 0xD8, 0x2A, 0xE7, 0x92, 0x91, 0x6A,
        0x73, 0xE9, 0xB1, 0x72, 0x39, 0x9F, 0x29, 0x9F, 0xA2, 0x98, 0xD3, 0x5F,
        0x5E, 0x58, 0x86, 0x65, 0x0F, 0xA1, 0x84, 0x65, 0x06, 0xD1, 0xDC, 0x8B,
        0xC9, 0xC7, 0x73, 0xC8, 0x8C, 0x6A, 0x2F, 0xE5, 0xC4, 0xAB, 0xD1, 0x1D,
        0x8A
    };

    const std::string domain = "jsonplaceholder.typicode.com";
    const std::string path = "/todos/1";
    const std::string request = XexUtils::Formatter::Format(
        "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "User-Agent: Xbox360/1.0\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n\r\n",
        path.c_str(),
        domain.c_str()
    );

    auto FlushSocket = [](XexUtils::Socket &socket) -> size_t {
        char buffer[2048] = {};
        size_t total = 0;

        for (;;)
        {
            int read = socket.Receive(buffer, sizeof(buffer) - 1);
            if (read <= 0)
                break;
            total += read;
        }

        return total;
    };

    It("connects using a secure socket", [=]() {
        HRESULT hr = S_OK;

        XexUtils::Socket secureSocket(domain, 443, true);
        hr = secureSocket.AddECTrustAnchor(EC_DN.data(), sizeof(EC_DN), EC_Q.data(), sizeof(EC_Q), XexUtils::Socket::Curve_secp384r1);
        TEST_EQ(hr, S_OK);

        hr = secureSocket.Connect();
        TEST_EQ(hr, S_OK);
    });

    It("connects using an insecure socket", [=]() {
        XexUtils::Socket secureSocket(domain, 80, false);

        HRESULT hr = secureSocket.Connect();
        TEST_EQ(hr, S_OK);
    });

    It("sends and receives data using a secure socket", [=]() {
        HRESULT hr = S_OK;

        XexUtils::Socket secureSocket(domain, 443, true);
        hr = secureSocket.AddECTrustAnchor(EC_DN.data(), sizeof(EC_DN), EC_Q.data(), sizeof(EC_Q), XexUtils::Socket::Curve_secp384r1);
        TEST_EQ(hr, S_OK);

        hr = secureSocket.Connect();
        TEST_EQ(hr, S_OK);

        int sent = secureSocket.Send(request.c_str(), request.size());
        TEST_EQ(sent, static_cast<int>(request.size()));

        size_t received = FlushSocket(secureSocket);
        TEST_EQ(received > 0, true);
    });

    It("sends and receives data using an insecure socket", [=]() {
        XexUtils::Socket insecureSocket(domain, 80, false);

        HRESULT hr = insecureSocket.Connect();
        TEST_EQ(hr, S_OK);

        int sent = insecureSocket.Send(request.c_str(), request.size());
        TEST_EQ(sent, static_cast<int>(request.size()));

        size_t received = FlushSocket(insecureSocket);
        TEST_EQ(received > 0, true);
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

    It("removes the hdd: symbolic link previously created with MountHdd", []() {
        Xam::MountHdd();
        std::ifstream file("hdd:\\launch.ini");
        TEST_EQ(file.is_open(), true);

        file.close();
        Xam::UnmountHdd();
        file.open("hdd:\\launch.ini");

        TEST_EQ(file.is_open(), false);
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

    ::Path();

    // Only run socket tests when connected to the internet
    uint32_t ethernetStatus = XNetGetEthernetLinkStatus();
    if (ethernetStatus & XNET_ETHERNET_LINK_ACTIVE || ethernetStatus & XNET_ETHERNET_LINK_WIRELESS)
        ::Socket();

    ::ValueOrPtr();

    ::Xam();

    TestRunner::Run();
}
