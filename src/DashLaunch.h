#pragma once

namespace XexUtils
{

typedef BOOL (*DLAUNCHGETOPTVALBYNAME)(const char *optionName, uint32_t *pOptionValue);
typedef BOOL (*DLAUNCHSETOPTVALBYNAME)(const char *optionName, uint32_t *pOptionValue);

class DashLaunch
{
public:
    static HRESULT Init();

    // Get the value of optionName as a uint32_t, 1 for true, 0 for false, pointer to the first character for strings.
    static DLAUNCHGETOPTVALBYNAME GetOptionValueByName;

    // Set the value of optionName as a uint32_t, 1 for true, 0 for false, pointer to the first character for strings.
    static DLAUNCHSETOPTVALBYNAME SetOptionValueByName;
};

}
