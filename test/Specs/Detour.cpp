#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

static XexUtils::Detour *pDetour = nullptr;

int NoBranch(int a, int b);
int NoBranchHook(int a, int b);
int PlainBranch(int a, int b);
int PlainBranchHook(int a, int b);
int LinkedBranch(int a, int b);
int LinkedBranchHook(int a, int b);
int ConditionalBranch(int a, int b);
int ConditionalBranchHook(int a, int b);
int AllRegisters(int a, int b, int c, int d, int e, int f, int g, int h);
int AllRegistersHook(int a, int b, int c, int d, int e, int f, int g, int h);
float FloatReturn(float a, float b);
float FloatReturnHook(float a, float b);

void Detour()
{
    Describe("Detour::Install");

    It("fails if the source function is null", []() {
        pDetour = new XexUtils::Detour(nullptr, NoBranchHook);
        HRESULT hr = pDetour->Install();
        delete pDetour;

        TEST_EQ(FAILED(hr), true);
    });

    It("fails if the destination function is null", []() {
        pDetour = new XexUtils::Detour(NoBranch, nullptr);
        HRESULT hr = pDetour->Install();
        delete pDetour;

        TEST_EQ(FAILED(hr), true);
    });

    It("fails if the Detour is already installed", []() {
        pDetour = new XexUtils::Detour(NoBranch, NoBranchHook);
        HRESULT hr1 = pDetour->Install();
        HRESULT hr2 = pDetour->Install();
        delete pDetour;

        TEST_EQ(SUCCEEDED(hr1), true);
        TEST_EQ(FAILED(hr2), true);
    });

    It("fails if the stub array is full", []() {
        XexUtils::Detour detours[MAX_DETOUR_COUNT];
        HRESULT hr = S_OK;

        for (size_t i = 0; i < MAX_DETOUR_COUNT; i++)
        {
            detours[i] = XexUtils::Detour(NoBranch, NoBranchHook);
            hr = detours[i].Install();
        }
        TEST_EQ(SUCCEEDED(hr), true);

        XexUtils::Detour extraDetour(NoBranch, NoBranchHook);
        hr = extraDetour.Install();

        TEST_EQ(FAILED(hr), true);
    });

    It("detours a function with no branch", []() {
        pDetour = new XexUtils::Detour(NoBranch, NoBranchHook);
        pDetour->Install();

        int value = NoBranch(2, 3);
        delete pDetour;

        TEST_EQ(value, 10);
    });

    It("detours a function with a plain branch", []() {
        pDetour = new XexUtils::Detour(PlainBranch, PlainBranchHook);
        pDetour->Install();

        int value = PlainBranch(2, 3);
        delete pDetour;

        TEST_EQ(value, 10);
    });

    It("detours a function with a linked branch", []() {
        pDetour = new XexUtils::Detour(LinkedBranch, LinkedBranchHook);
        pDetour->Install();

        int value = LinkedBranch(2, 3);
        delete pDetour;

        TEST_EQ(value, 10);
    });

    It("detours a function with a conditional branch (condition is met)", []() {
        pDetour = new XexUtils::Detour(ConditionalBranch, ConditionalBranchHook);
        pDetour->Install();

        int value = ConditionalBranch(3, 3);
        delete pDetour;

        TEST_EQ(value, 12);
    });

    It("detours a function with a conditional branch (condition is not met)", []() {
        pDetour = new XexUtils::Detour(ConditionalBranch, ConditionalBranchHook);
        pDetour->Install();

        int value = ConditionalBranch(2, 3);
        delete pDetour;

        TEST_EQ(value, 10);
    });

    It("calls the original and preserves all argument registers", []() {
        pDetour = new XexUtils::Detour(AllRegisters, AllRegistersHook);
        pDetour->Install();

        int value = AllRegisters(1, 2, 3, 4, 5, 6, 7, 8);
        delete pDetour;

        TEST_EQ(value, 72);
    });

    It("calling the original preserves the return value for floating point types", []() {
        pDetour = new XexUtils::Detour(FloatReturn, FloatReturnHook);
        pDetour->Install();

        float value = FloatReturn(1.5f, 2.5f);
        delete pDetour;

        TEST_EQ(value, 8.0f);
    });

    Describe("Detour::Remove");

    It("removes a the detour", []() {
        pDetour = new XexUtils::Detour(NoBranch, NoBranchHook);
        pDetour->Install();

        int valueWhileDetoured = NoBranch(2, 3);

        pDetour->Remove();

        doSync(NoBranch);
        int valueAfterDetour = NoBranch(2, 3);

        delete pDetour;

        TEST_EQ(valueWhileDetoured, 10);
        TEST_EQ(valueAfterDetour, 5);
    });
}

__declspec(naked) int NoBranch(int a, int b)
{
    __asm
    {
        add     r3, r3, r4
        nop
        nop
        nop
        blr
    }
}

int NoBranchHook(int a, int b)
{
    return pDetour->GetOriginal<decltype(&NoBranch)>()(a * 2, b * 2);
}

__declspec(naked) int PlainBranch(int a, int b)
{
    __asm
    {
        b       sum
        nop
        nop
        nop

        sum:
        add     r3, r3, r4
        blr
    }
}

int PlainBranchHook(int a, int b)
{
    return pDetour->GetOriginal<decltype(&PlainBranch)>()(a * 2, b * 2);
}

__declspec(naked) int Sum(int a, int b)
{
    __asm
    {
        add     r3, r3, r4
        blr
    }
}

__declspec(naked) int LinkedBranch(int a, int b)
{
    __asm
    {
        mflr    r0
        stw     r0, 8h(r1)

        bl      Sum
        nop
        nop
        nop

        lwz     r0, 8h(r1)
        mtlr    r0
        blr
    }
}

int LinkedBranchHook(int a, int b)
{
    return pDetour->GetOriginal<decltype(&LinkedBranch)>()(a * 2, b * 2);
}

__declspec(naked) int ConditionalBranch(int a, int b)
{
    __asm
    {
        cmpw    r3, r4
        beq     equal
        nop
        nop
        nop

        equal:
        add     r3, r3, r4
        blr
    }
}

int ConditionalBranchHook(int a, int b)
{
    return pDetour->GetOriginal<decltype(&ConditionalBranch)>()(a * 2, b * 2);
}

__declspec(naked) int AllRegisters(int a, int b, int c, int d, int e, int f, int g, int h)
{
    __asm
    {
        add     r3, r3, r4
        add     r3, r3, r5
        add     r3, r3, r6
        add     r3, r3, r7
        add     r3, r3, r8
        add     r3, r3, r9
        add     r3, r3, r10
        blr
    }
}

int AllRegistersHook(int a, int b, int c, int d, int e, int f, int g, int h)
{
    return pDetour->GetOriginal<decltype(&AllRegisters)>()(a * 2, b * 2, c * 2, d * 2, e * 2, f * 2, g * 2, h * 2);
}

__declspec(naked) float FloatReturn(float a, float b)
{
    __asm
    {
        fadds   fr1, fr1, fr2
        nop
        nop
        nop
        blr
    }
}

float FloatReturnHook(float a, float b)
{
    return pDetour->GetOriginal<decltype(&FloatReturn)>()(a * 2.0f, b * 2.0f);
}
