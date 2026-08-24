#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void General()
{
    Describe("ResolveExport(const std::string &, uint32_t)");

    It("returns a valid pointer when given a valid module name and ordinal", []() {
        void *pFunc = ResolveExport("xam.xex", 656); // XNotifyQueueUI

        TEST_NEQ(reinterpret_cast<uintptr_t>(pFunc), reinterpret_cast<uintptr_t>(nullptr));
    });

    It("returns nullptr when given an invalid module name", []() {
        void *pFunc = ResolveExport("invalid.xex", 1);

        TEST_EQ(reinterpret_cast<uintptr_t>(pFunc), reinterpret_cast<uintptr_t>(nullptr));
    });

    It("returns nullptr when given an invalid ordinal", []() {
        void *pFunc = ResolveExport("xam.xex", 0xFFFFFF);

        TEST_EQ(reinterpret_cast<uintptr_t>(pFunc), reinterpret_cast<uintptr_t>(nullptr));
    });
}
