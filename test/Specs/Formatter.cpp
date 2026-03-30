// NOTE: This file has a UTF-8 with BOM encoding, this is required for the
// Formatter::ToWide and Formatter::ToNarrow tests to pass because they use multibyte
// characters declared in the code. If those tests stop passing, make sure the encoding
// of this file is still correct.

#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Formatter()
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

    It("converts an std::string to an std::wstring using ANSI encoding", []() {
        std::string narrow = "é";
        std::wstring wide = Formatter::ToWide(narrow, CP_ACP);

        TEST_EQ_W(wide, L"é");
    });

    It("converts an std::string to an std::wstring using UTF8 encoding", []() {
        std::string narrow = "\xE7\x9A\x84"; // 的
        std::wstring wide = Formatter::ToWide(narrow, CP_UTF8);

        TEST_EQ_W(wide, L"的");
    });

    Describe("Formatter::ToNarrow");

    It("converts an std::wstring to an std::string using ANSI encoding", []() {
        std::wstring wide = L"é";
        std::string narrow = Formatter::ToNarrow(wide, CP_ACP);

        TEST_EQ(narrow, "é");
    });

    It("converts an std::wstring to an std::string using UTF8 encoding", []() {
        std::wstring wide = L"的";
        std::string narrow = Formatter::ToNarrow(wide, CP_UTF8);

        TEST_EQ(narrow, "\xE7\x9A\x84"); // 的
    });
}
