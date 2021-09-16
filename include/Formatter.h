#pragma once

namespace XexUtils
{
namespace Formatter
{
    std::string Format(LPCSTR format, ...);

    std::wstring ToWide(CONST std::string& narrowString);
}
}
