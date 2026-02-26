#include "TestRunner.h"

#include <xtl.h>

#include <vector>

#include <XexUtils.h>

namespace TestRunner
{

static double s_TicksPerMillisecond;
static uint64_t s_TotalTickCount;
static size_t s_PassingTests;
static std::vector<std::string> s_ErrorMessages;

void Describe(const std::string &sectionName)
{
    XexUtils::Log::Print("\n%s", sectionName.c_str());
}

void It(const std::string &testName, std::function<void()> testFunction)
{
    XASSERT(s_TicksPerMillisecond != 0);

    // Keep track of the fail count before running the test
    size_t previousFailCount = s_ErrorMessages.size();

    // Mesure time before running the test
    LARGE_INTEGER startTickCount = {};
    QueryPerformanceCounter(&startTickCount);

    // Run the test
    testFunction();

    // Mesure time after running the test
    LARGE_INTEGER endTickCount = {};
    QueryPerformanceCounter(&endTickCount);

    // Calculate how long the test took to run
    uint64_t ticksElapsed = endTickCount.QuadPart - startTickCount.QuadPart;
    double millisecondsElapsed = static_cast<double>(ticksElapsed) / s_TicksPerMillisecond;

    // Increment the global timer
    s_TotalTickCount += ticksElapsed;

    // Get the fail count after running the test
    size_t currentFailCount = s_ErrorMessages.size();

    // If the fail count hasn't changed, the test passed
    if (currentFailCount == previousFailCount)
    {
        XexUtils::Log::Print(
            "    [-]  %s (%.4fms)",
            testName.c_str(),
            millisecondsElapsed
        );
        s_PassingTests++;
    }
    else
    {
        XexUtils::Log::Print(
            "    [X]  %s. Error: %s (%.4fms)",
            testName.c_str(),
            s_ErrorMessages.back().c_str(),
            millisecondsElapsed
        );
    }
}

void Start()
{
    // Get the clock resolution
    LARGE_INTEGER ticksPerSecond = {};
    QueryPerformanceFrequency(&ticksPerSecond);
    s_TicksPerMillisecond = static_cast<double>(ticksPerSecond.QuadPart) * 0.001;
}

void End()
{
    XASSERT(s_TicksPerMillisecond != 0);
    XASSERT(s_TotalTickCount != 0);

    // Calculate how long the tests took to run
    double millisecondsElapsed = static_cast<double>(s_TotalTickCount) / s_TicksPerMillisecond;

    XexUtils::Log::Print("");

    // Print all the errors
    size_t failedTests = s_ErrorMessages.size();
    if (failedTests > 0)
    {
        for (size_t i = 0; i < s_ErrorMessages.size(); i++)
            XexUtils::Log::Print("[X]  %s", s_ErrorMessages[i].c_str());

        XexUtils::Log::Print("");
    }

    // Print the final recap
    XexUtils::Log::Print(
        "%d test%s passed, %d test%s failed in %.4fms",
        s_PassingTests,
        s_PassingTests != 1 ? "s" : "",
        failedTests,
        failedTests != 1 ? "s" : "",
        millisecondsElapsed
    );
}

void PushError(const std::string &errorMessage)
{
    s_ErrorMessages.push_back(errorMessage);
}

void PushError(const std::wstring &errorMessage)
{
    PushError(XexUtils::Formatter::ToNarrow(errorMessage));
}

}
