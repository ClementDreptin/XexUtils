#include "pch.h"
#include "Path.h"

#include "Formatter.h"

namespace XexUtils
{

Path::Path()
{
}

Path::Path(const std::string &path)
    : m_Text(path)
{
}

Path::Path(const std::wstring &path)
    : m_Text(Formatter::ToNarrow(path))
{
}

Path Path::Drive() const
{
    // We can't use _splitpath_s here because it only accept one-character-long drive names
    // and, unlike Windows, Xbox 360 drive names are typical full words

    size_t colonPos = m_Text.find_first_of(':');

    if (colonPos == std::string::npos)
        return Path();

    return Path(m_Text.substr(0, colonPos + 1));
}

Path Path::Directory() const
{
    if (IsDrive())
        return Path();

    size_t colonPos = m_Text.find_first_of(':');
    const std::string &textWithoutDrive = colonPos != std::string::npos ? m_Text.substr(colonPos + 1) : m_Text;
    char directory[_MAX_DIR] = {};

    errno_t error = _splitpath_s(
        textWithoutDrive.c_str(),
        nullptr, 0,
        directory, sizeof(directory),
        nullptr, 0,
        nullptr, 0
    );
    HANDLE_SPLITPATH_ERROR(error);

    return Path(directory);
}

Path Path::Basename() const
{
    if (IsDrive())
        return Path();

    char basename[_MAX_FNAME] = {};

    errno_t error = _splitpath_s(
        m_Text.c_str(),
        nullptr, 0,
        nullptr, 0,
        basename, sizeof(basename),
        nullptr, 0
    );
    HANDLE_SPLITPATH_ERROR(error);

    return Path(basename);
}

Path Path::Extension() const
{
    if (IsDrive())
        return Path();

    char extension[_MAX_EXT] = {};

    errno_t error = _splitpath_s(
        m_Text.c_str(),
        nullptr, 0,
        nullptr, 0,
        nullptr, 0,
        extension, sizeof(extension)
    );
    HANDLE_SPLITPATH_ERROR(error);

    return Path(extension);
}

Path Path::Filename() const
{
    if (IsDrive())
        return Path();

    char basename[_MAX_FNAME] = {};
    char extension[_MAX_EXT] = {};

    errno_t error = _splitpath_s(
        m_Text.c_str(),
        nullptr, 0,
        nullptr, 0,
        basename, sizeof(basename),
        extension, sizeof(extension)
    );
    HANDLE_SPLITPATH_ERROR(error);

    return Path(std::string(basename) + std::string(extension));
}

Path Path::Parent() const
{
    Path directory = Directory();
    bool isRootDirectory = directory.m_Text == "\\";

    Path parentDirectory = IsDirectory() && !isRootDirectory ? Path(m_Text.substr(0, m_Text.size() - 1)).Directory() : directory;

    return Path(Drive().m_Text + parentDirectory.m_Text);
}

bool Path::IsDrive() const
{
    return m_Text.back() == ':';
}

bool Path::IsDirectory() const
{
    return m_Text.back() == '\\';
}

}
