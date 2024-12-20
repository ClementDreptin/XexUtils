#include "pch.h"
#include "specs.h"

extern ATG::Console g_Console;

static void Vec2()
{
    XexUtils::Math::vec2 v(1.0f, 2.0f);
    XexUtils::Math::vec2 result = v + v;

    if (result.x != 2.0f || result.y != 4.0f)
    {
        g_Console.Format("[FAIL]: expected x to be 2.0f and y to be 4.0f");
        return;
    }

    g_Console.Format("[PASS]: vec2");
}

void RunTests()
{
    Vec2();
}
