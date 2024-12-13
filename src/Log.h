#pragma once

namespace XexUtils
{
namespace Log
{

void Info(const char *message, ...);

void Info(const std::string &message);

void Info(const wchar_t *message, ...);

void Info(const std::wstring &message);

void Error(const char *message, ...);

void Error(const std::string &message);

void Error(const wchar_t *message, ...);

void Error(const std::wstring &message);

}
}
