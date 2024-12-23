#include "pch.h"
#include "DashLaunch.h"

#include "Memory.h"

#define LAUNCH_MODULE "launch.xex"

namespace XexUtils
{
namespace DashLaunch
{

typedef enum _DL_ORDINALS
{
    DL_ORDINALS_GETOPTVALBYNAME = 9,
    DL_ORDINALS_SETOPTVALBYNAME = 10,
} DL_ORDINALS;

DLAUNCHGETOPTVALBYNAME GetOptionValueByName = nullptr;
DLAUNCHSETOPTVALBYNAME SetOptionValueByName = nullptr;

HRESULT Init()
{
    GetOptionValueByName = static_cast<DLAUNCHGETOPTVALBYNAME>(Memory::ResolveFunction(LAUNCH_MODULE, DL_ORDINALS_GETOPTVALBYNAME));
    if (GetOptionValueByName == nullptr)
    {
        DebugPrint("[XexUtils][DashLaunch]: Error: Could not resolve the GetOptionValueByName function");
        return E_FAIL;
    }

    SetOptionValueByName = static_cast<DLAUNCHSETOPTVALBYNAME>(Memory::ResolveFunction(LAUNCH_MODULE, DL_ORDINALS_SETOPTVALBYNAME));
    if (SetOptionValueByName == nullptr)
    {
        DebugPrint("[XexUtils][DashLaunch]: Error: Could not resolve the SetOptionValueByName function");
        return E_FAIL;
    }

    return S_OK;
}

}
}
