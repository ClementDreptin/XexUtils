#pragma once

namespace XexUtils
{

/// @brief A class representing a file system path.
class Path
{
public:
    /// @brief Creates an empty `Path`.
    Path();

    /// @brief Creates a `Path` object from a given string.
    /// @param path The string representing the path.
    Path(const std::string &path);

    /// @brief Creates a `Path` object from a given string.
    /// @param path The string representing the path.
    Path(const char *path);

    /// @brief Concatenates a generic type with a `Path` object.
    /// @tparam T The type of the left operand.
    /// @param left The left operand of the concatenation.
    /// @param path The `Path` object to concatenate.
    /// @return The resulting string from the concatenation.
    template<typename T>
    inline friend std::string operator+(const T &left, const Path &path)
    {
        return left + path.String();
    }

    /// @brief Concatenates a `Path` object with a generic type.
    /// @tparam T The type of the right operand.
    /// @param path The `Path` object to concatenate.
    /// @param right The right operand of the concatenation.
    /// @return The resulting string from the concatenation.
    template<typename T>
    inline friend std::string operator+(const Path &path, const T &right)
    {
        return path.String() + right;
    }

    /// @brief Outputs the `Path` object to an output stream.
    /// @param stream The output stream.
    /// @param path The `Path` object to output.
    /// @return The output stream with the `Path` object's string representation.
    inline friend std::ostream &operator<<(std::ostream &stream, const Path &path)
    {
        return stream << path.String();
    }

    /// @brief Appends a `Path` to the current `Path` object.
    /// @param path The `Path` to append.
    /// @return A reference to the modified `Path` object.
    inline Path &operator/=(const Path &path)
    {
        return Append(path);
    }

    /// @brief Combines two `Path` objects.
    /// @param path The left `Path` object.
    /// @param right The right `Path` object.
    /// @return The resulting `Path` from the combination.
    friend Path operator/(const Path &path, const Path &right)
    {
        Path tmp = path;
        tmp /= right;
        return tmp;
    }

    /// @brief Compares two `Path` objects for equality.
    /// @param left The left `Path` object.
    /// @param right The right `Path` object.
    /// @return True if the `Path` objects are equal, false otherwise.
    inline friend bool operator==(const Path &left, const Path &right)
    {
        return left.Compare(right);
    }

    /// @brief Compares two `Path` objects for inequality.
    /// @param left The left `Path` object.
    /// @param right The right `Path` object.
    /// @return True if the `Path` objects are not equal, false otherwise.
    inline friend bool operator!=(const Path &left, const Path &right)
    {
        return !(left == right);
    }

    /// @brief Gets the string representation of the `Path`.
    /// @return The string representation of the `Path`.
    inline const std::string &String() const { return m_Path; }

    /// @brief Gets the drive part of the `Path`.
    /// @return The drive part of the `Path`.
    Path Drive() const;

    /// @brief Gets the basename part of the `Path`.
    /// @return The basename part of the `Path`.
    Path Basename() const;

    /// @brief Gets the extension part of the `Path`.
    /// @return The extension part of the `Path`.
    Path Extension() const;

    /// @brief Gets the filename part of the `Path`.
    /// @return The filename part of the `Path`.
    Path Filename() const;

    /// @brief Gets the parent directory part of the `Path`.
    /// @return The parent directory part of the `Path`.
    Path Parent() const;

    /// @brief Appends a `Path` to the current `Path` object.
    /// @param path The `Path` to append.
    /// @return A reference to the modified `Path` object.
    Path &Append(const Path &path);

    /// @brief Compares the current `Path` object with another `Path` object.
    /// @param other The other `Path` object to compare with.
    /// @return True if the `Path` objects are equal, false otherwise.
    bool Compare(const Path &other) const;

    /// @brief Checks if the `Path` is empty.
    /// @return `true` if the `Path` is empty, `false` otherwise.
    bool IsEmpty() const;

    /// @brief Checks if the `Path` is a root path.
    /// @return `true` if the `Path` is a root path, `false` otherwise.
    bool IsRoot() const;

private:
    std::string m_Path;

    static const char s_Separator;
};

}
