#pragma once

namespace XexUtils
{
namespace Formatter
{

std::string Format(const char *format, ...);

std::wstring Format(const wchar_t *format, ...);

std::wstring ToWide(const std::string &narrowString);

std::string ToNarrow(const std::wstring &wideString);

}
}
