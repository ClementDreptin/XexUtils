#pragma once

namespace XexUtils
{
namespace Dashlaunch
{

typedef BOOL (*DLAUNCHGETOPTVALBYNAME)(const char *optionName, uint32_t *pOptionValue);
typedef BOOL (*DLAUNCHSETOPTVALBYNAME)(const char *optionName, uint32_t *pOptionValue);

/// @brief Initializes the Dashlaunch module.
///
/// Get pointers to the 9th and 10th functions exported by the `launch.xex` module
/// which, respectively, get and set Dashlaunch options by their names. It is necessary
/// to call this function successfully before using the `GetOptionValueByName` and
/// `SetOptionValueByName` functions.
///
/// This function can fail if Dashlaunch isn't loaded on the system.
///
/// @return `S_OK` on success, `E_FAIL` on error.
HRESULT Init();

/// @brief Gets the value of a Dashlaunch option by its name.
///
/// The value is always stored in a `uint32_t`. `1` for true, `0` for false and the
/// address of the first character for strings.
///
/// This function can fail if `optionName` doesn't correspond to any
/// existing Dashlaunch option.
///
/// @param optionName The name of the option.
/// @param pOptionValue A pointer to a `uint32_t` to store the value.
/// @return `TRUE` on success, `FALSE` on error.
extern DLAUNCHGETOPTVALBYNAME GetOptionValueByName;

/// @brief Sets the value of a Dashlaunch option by its name.
///
/// The value is always stored in a `uint32_t`. `1` for true, `0` for false and the
/// address of the first character for strings.
///
/// This function can fail if `optionName` doesn't correspond to any
/// existing Dashlaunch option.
///
/// @param optionName The name of the option.
/// @param pOptionValue A pointer to the value as a `uint32_t`.
/// @return `TRUE` on success, `FALSE` on error.
extern DLAUNCHSETOPTVALBYNAME SetOptionValueByName;

}
}
