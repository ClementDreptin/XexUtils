#include "pch.h"
#include "TestRunner.h"

namespace TestRunner
{

static size_t s_PassingTests;
static std::vector<std::string> s_ErrorMessages;

void Describe(const std::string &sectionName)
{
    XexUtils::Log::Print("\n%s", sectionName.c_str());
}

void It(const std::string &testName, std::function<void()> testFunction)
{
    size_t previousFailCount = s_ErrorMessages.size();
    testFunction();
    size_t currentFailCount = s_ErrorMessages.size();

    if (currentFailCount == previousFailCount)
    {
        XexUtils::Log::Print("    [-]  %s", testName.c_str());
        s_PassingTests++;
    }
    else
        XexUtils::Log::Print("    [X]  %s. Error: %s", testName.c_str(), s_ErrorMessages.back().c_str());
}

void DisplayRecap()
{
    size_t failedTests = s_ErrorMessages.size();

    XexUtils::Log::Print("");

    if (failedTests > 0)
    {
        // Recap the error messages
        for (size_t i = 0; i < s_ErrorMessages.size(); i++)
            XexUtils::Log::Print("[X]  %s", s_ErrorMessages[i].c_str());

        XexUtils::Log::Print("");
    }

    // Print the final recap
    XexUtils::Log::Print(
        "%d test%s passed, %d test%s failed",
        s_PassingTests,
        s_PassingTests != 1 ? "s" : "",
        failedTests,
        failedTests != 1 ? "s" : ""
    );
}

void TestRunner::PushError(const std::string &errorMessage)
{
    s_ErrorMessages.push_back(errorMessage);
}

void PushError(const std::wstring &errorMessage)
{
    PushError(XexUtils::Formatter::ToNarrow(errorMessage));
}

}
