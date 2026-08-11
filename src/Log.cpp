#include "pch.h"
#include "Log.h"

namespace XexUtils
{
namespace Log
{

void Print(const char *format, ...)
{
    XASSERT(format != nullptr);

    // Determine the required buffer size.
    va_list args;
    va_start(args, format);
    size_t requiredBufferSize = vsnprintf(nullptr, 0, format, args) + 1; // +1 for '\n'.
    va_end(args);

    // By default, we use a fixed size buffer to perform the printf formatting.
    char fixedBuffer[2048] = {};
    char *bufferToUse = fixedBuffer;
    bool dynamicBufferUsed = false;

    // If the fixed size buffer isn't big enough, dynamically allocate a bigger one.
    if (requiredBufferSize > ARRAYSIZE(fixedBuffer))
    {
        bufferToUse = new char[requiredBufferSize]();
        dynamicBufferUsed = true;
    }

    // Format the string into the buffer.
    va_start(args, format);
    vsnprintf_s(bufferToUse, requiredBufferSize, _TRUNCATE, format, args);
    va_end(args);

    // Append a newline.
    bufferToUse[requiredBufferSize - 1] = '\n';

    // Write the content of the buffer to stdout in chunks. This is needed because, when
    // connected to a remote debugger, there a limit in how much text can be sent over the
    // network in a single write. This limit seems to be different with every function
    // that can write to stdout. printf, puts, fwrite and DbgPrint were tested and they
    // all seem to have a different limit. A chunk size of 128 bytes seems to be small
    // enough when using fwrite.
    const size_t chunkSize = 128;
    for (size_t i = 0; i < requiredBufferSize; i += chunkSize)
    {
        size_t currentChunkSize = std::min<size_t>(chunkSize, requiredBufferSize - i);
        fwrite(bufferToUse + i, 1, currentChunkSize, stdout);
    }

    // If we had to use a dynamic buffer, free it.
    if (dynamicBufferUsed)
        delete[] bufferToUse;
}

void Print(const std::string &message)
{
    Print(message.c_str());
}

void Print(const wchar_t *format, ...)
{
    XASSERT(format != nullptr);

    // Determine the required buffer size.
    va_list args;
    va_start(args, format);
    size_t requiredBufferSize = _vsnwprintf(nullptr, 0, format, args) + 1; // +1 for L'\n'.
    va_end(args);

    // By default, we use a fixed size buffer to perform the printf formatting.
    wchar_t fixedBuffer[2048] = {};
    wchar_t *bufferToUse = fixedBuffer;
    bool dynamicBufferUsed = false;

    // If the fixed size buffer isn't big enough, dynamically allocate a bigger one.
    if (requiredBufferSize > ARRAYSIZE(fixedBuffer))
    {
        bufferToUse = new wchar_t[requiredBufferSize]();
        dynamicBufferUsed = true;
    }

    // Format the string into the buffer.
    va_start(args, format);
    _vsnwprintf_s(bufferToUse, requiredBufferSize, _TRUNCATE, format, args);
    va_end(args);

    // Append a newline.
    bufferToUse[requiredBufferSize - 1] = L'\n';

    // Write the content of the buffer to stdout in chunks. This is needed because, when
    // connected to a remote debugger, there a limit in how much text can be sent over the
    // network in a single write. This limit seems to be different with every function
    // that can write to stdout. printf, puts, fwrite and DbgPrint were tested and they
    // all seem to have a different limit. A chunk size of 128 bytes seems to be small
    // enough when using fwrite.
    const size_t chunkSize = 128;
    for (size_t i = 0; i < requiredBufferSize; i += chunkSize)
    {
        size_t currentChunkSize = std::min<size_t>(chunkSize, requiredBufferSize - i);

        // It's not ideal to go through the printf formatting again but I couldn't find
        // a way to write a wchar_t buffer to stdout without converting to chars first.
        wprintf_s(L"%.*s", currentChunkSize, bufferToUse + i);
    }

    // If we had to use a dynamic buffer, free it.
    if (dynamicBufferUsed)
        delete[] bufferToUse;
}

void Print(const std::wstring &message)
{
    Print(message.c_str());
}

}
}
