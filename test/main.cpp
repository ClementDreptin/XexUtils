#include "pch.h"

ATG::Console g_Console;

static void Init()
{
    HRESULT hr = g_Console.Create("game:\\Media\\Fonts\\Arial_16.xpr", D3DCOLOR_XRGB(31, 0, 95), D3DCOLOR_XRGB(255, 255, 255));

    if (FAILED(hr))
        ATG::FatalError("Failed to create console: %x\n", hr);

    g_Console.Format("Console initialized\n");
}

static void RunTests()
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

void __cdecl main()
{
    Init();

    RunTests();

    for (;;)
    {
    }
}
