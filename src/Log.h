#pragma once

namespace XexUtils
{

class Log
{
public:
    static void Info(const char *message, ...);

    inline static void Info(const std::string &message) { Info(message.c_str()); }

    static void Error(const char *message, ...);

    inline static void Error(const std::string &message) { Error(message.c_str()); }

private:
    static void Print(const char *format, const va_list args, std::ostream &outputStream);
};

}
