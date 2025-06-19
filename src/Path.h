#pragma once

namespace XexUtils
{

class Path
{
public:
    Path();

    Path(const std::string &path);

    Path(const std::wstring &path);

    Path Drive() const;

    Path Directory() const;

    Path Basename() const;

    Path Extension() const;

    Path Filename() const;

    Path Parent() const;

    inline const std::string &String() const { return m_Text; }

private:
    std::string m_Text;

    bool IsDrive() const;

    bool IsDirectory() const;
};

#define HANDLE_SPLITPATH_ERROR(error) \
    if (error != 0) \
    { \
        DebugPrint( \
            "[XexUtils][Xam]: Error: Couldn't create a Path instance from \"%s\". Error returned by _splitpath_s: %d", \
            m_Text.c_str(), \
            error \
        ); \
        return Path(); \
    }

}
