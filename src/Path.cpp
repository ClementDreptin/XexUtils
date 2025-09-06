#include "pch.h"
#include "Path.h"

namespace XexUtils
{

const char Path::s_Separator = '\\';

Path::Path()
{
}

Path::Path(const std::string &path)
    : m_Path(path)
{
}

Path::Path(const char *path)
    : m_Path(path)
{
}

Path Path::Drive() const
{
    size_t colonPos = m_Path.find_first_of(':');

    if (colonPos == std::string::npos)
        return Path();

    return Path(m_Path.substr(0, colonPos + 1));
}

Path Path::Basename() const
{
    size_t lastSeparatorPos = m_Path.find_last_of(s_Separator);
    size_t lastDotPos = m_Path.find_last_of('.');
    size_t colonPos = m_Path.find_first_of(':');
    size_t characterBeforeFileNamePos = lastSeparatorPos != std::string::npos ? lastSeparatorPos : colonPos;

    // Case of path only containing a drive
    if (colonPos == m_Path.size() - 1)
        return Path();

    // Case of file name starting with a dot and no extension (like .gitignore)
    if (lastDotPos == characterBeforeFileNamePos + 1)
        return Path(m_Path.substr(characterBeforeFileNamePos + 1));

    return Path(m_Path.substr(characterBeforeFileNamePos + 1, lastDotPos - characterBeforeFileNamePos - 1));
}

Path Path::Extension() const
{
    size_t lastSeparatorPos = m_Path.find_last_of(s_Separator);
    size_t lastDotPos = m_Path.find_last_of('.');
    size_t colonPos = m_Path.find_first_of(':');
    size_t characterBeforeFileNamePos = lastSeparatorPos != std::string::npos ? lastSeparatorPos : colonPos;

    if (lastDotPos == std::string::npos || lastDotPos == characterBeforeFileNamePos + 1)
        return Path();

    return Path(m_Path.substr(lastDotPos));
}

Path Path::Filename() const
{
    return Basename().String() + Extension().String();
}

Path Path::Parent() const
{
    if (IsEmpty())
        return Path();

    if (IsRoot())
        return *this;

    // When the path is a directory (so ends with the separator), we make the offset
    // to be one character before so that lastSeparatorPos doesn't point the very last
    // separator but the one before
    size_t offset = std::string::npos;
    if (m_Path.back() == s_Separator)
        offset = m_Path.size() - 2;

    size_t lastSeparatorPos = m_Path.find_last_of(s_Separator, offset);

    // Handle absolute path case
    if (lastSeparatorPos == 0)
        return Path(std::string(1, s_Separator));

    if (lastSeparatorPos == std::string::npos)
    {
        Path drive = Drive();
        if (!drive.IsEmpty())
            return drive;

        return Path();
    }

    return Path(m_Path.substr(0, lastSeparatorPos));
}

Path &Path::Append(const Path &path)
{
    if (!IsEmpty() && m_Path.back() != s_Separator)
        m_Path += s_Separator;

    m_Path += path.String();

    return *this;
}

bool Path::Compare(const Path &other) const
{
    return String() == other.String();
}

bool Path::IsEmpty() const
{
    return m_Path.empty();
}

bool Path::IsRoot() const
{
    if (IsEmpty())
        return true;

    // If the path is a path of a file it can't be the root of drive
    if (!Filename().IsEmpty())
        return false;

    size_t lastSeparatorPos = m_Path.find_last_of(s_Separator);
    size_t colonPos = m_Path.find_first_of(':');

    return colonPos == m_Path.size() - 1 || lastSeparatorPos == colonPos + 1;
}

}
