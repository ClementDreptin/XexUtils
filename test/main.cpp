#include "pch.h"

ATG::Console g_Console;

static void Init()
{
    HRESULT hr = g_Console.Create("game:\\Media\\Fonts\\Arial_16.xpr", D3DCOLOR_XRGB(31, 0, 95), D3DCOLOR_XRGB(255, 255, 255));

    if (FAILED(hr))
        ATG::FatalError("Failed to create console: %x\n", hr);

    g_Console.Format("Console initialized\n");
}

void __cdecl main()
{
    Init();

    for (;;)
    {
    }
}
