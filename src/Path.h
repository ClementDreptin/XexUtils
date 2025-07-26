#pragma once

namespace XexUtils
{

class Path
{
public:
    Path();
    Path(const std::string &path);

    template<typename T>
    inline friend std::string operator+(const T &left, const Path &path)
    {
        return left + path.String();
    }

    template<typename T>
    inline friend std::string operator+(const Path &path, const T &right)
    {
        return path.String() + right;
    }

    inline friend std::ostream &operator<<(std::ostream &stream, const Path &path)
    {
        return stream << path.String();
    }

    inline Path &operator/=(const Path &path)
    {
        return Append(path);
    }

    friend Path operator/(const Path &path, const Path &right)
    {
        Path tmp = path;
        tmp /= right;
        return tmp;
    }

    inline friend bool operator==(const Path &left, const Path &right)
    {
        return left.Compare(right);
    }

    inline friend bool operator!=(const Path &left, const Path &right)
    {
        return !(left == right);
    }

    inline const std::string &String() const { return m_Path; }

    Path Drive() const;

    Path Basename() const;

    Path Extension() const;

    Path Filename() const;

    Path Parent() const;

    Path &Append(const Path &path);

    bool Compare(const Path &other) const;

    bool IsEmpty() const;

    bool IsRoot() const;

private:
    std::string m_Path;

    static const char s_Separator;
};

}
