#pragma once

namespace XexUtils
{

/// @brief A tag type to represent an empty `Optional`.
struct NullOpt
{
};

/// @brief A class to represent a value that may or may not be there.
/// @tparam T The underlying type to store.
template<typename T>
class Optional
{
public:
    /// @brief Creates an empty `Optional`.
    Optional()
        : m_HasValue(false)
    {
    }

    /// @brief Creates an empty `Optional` using the `NullOpt` tag.
    /// @param nullOpt Tag to indicate an empty `Optional`.
    Optional(NullOpt)
        : m_HasValue(false)
    {
    }

    /// @brief Creates an `Optional` from a value.
    /// @param value The value.
    Optional(const T &value)
        : m_HasValue(true)
    {
        new (&m_Storage) T(value);
    }

    /// @brief Creates an `Optional` from an rvalue.
    /// @param value The rvalue.
    Optional(T &&value)
        : m_HasValue(true)
    {
        new (&m_Storage) T(std::move(value));
    }

    /// @brief Copies `other` to the current `Optional`.
    /// @param other The `Optional` to copy.
    Optional(const Optional &other)
        : m_HasValue(other.m_HasValue)
    {
        if (m_HasValue)
            new (&m_Storage) T(*other);
    }

    /// @brief Moves `other` into the current `Optional`.
    ///
    /// After this operation, `other` will be empty.
    ///
    /// @param other The `Optional` to move.
    Optional(Optional &&other)
        : m_HasValue(other.m_HasValue)
    {
        if (m_HasValue)
        {
            new (&m_Storage) T(std::move(*other));
            other.Destroy();
        }
    }

    /// @brief Destroys the `Optional` and its stored value, if any.
    ~Optional()
    {
        Destroy();
    }

    /// @brief Resets the `Optional` to an empty state.
    /// @return A reference to the `Optional`.
    Optional &operator=(NullOpt)
    {
        Destroy();
        return *this;
    }

    /// @brief Assigns a value to the `Optional`.
    /// @param value The value.
    /// @return A reference to the `Optional`.
    Optional &operator=(const T &value)
    {
        if (m_HasValue)
        {
            **this = value;
        }
        else
        {
            new (&m_Storage) T(value);
            m_HasValue = true;
        }

        return *this;
    }

    /// @brief Moves a value into the `Optional`.
    /// @param value The value.
    /// @return A reference to the `Optional`.
    Optional &operator=(T &&value)
    {
        if (m_HasValue)
        {
            **this = std::move(value);
        }
        else
        {
            new (&m_Storage) T(std::move(value));
            m_HasValue = true;
        }

        return *this;
    }

    /// @brief Copies an `Optional` to another.
    /// @param other The `Optional` to copy.
    /// @return A reference to the `Optional`.
    Optional &operator=(const Optional &other)
    {
        if (m_HasValue && other.m_HasValue)
        {
            **this = *other;
        }
        else if (m_HasValue && !other.m_HasValue)
        {
            Destroy();
        }
        else if (!m_HasValue && other.m_HasValue)
        {
            new (&m_Storage) T(*other);
            m_HasValue = true;
        }

        return *this;
    }

    /// @brief Moves an `Optional` into another.
    ///
    /// After this operation, `other` will be empty.
    ///
    /// @param other The `Optional` to move.
    /// @return A reference to the `Optional`.
    Optional &operator=(Optional &&other)
    {
        if (m_HasValue && other.m_HasValue)
        {
            **this = std::move(*other);
            other.Destroy();
        }
        else if (m_HasValue && !other.m_HasValue)
        {
            Destroy();
        }
        else if (!m_HasValue && other.m_HasValue)
        {
            new (&m_Storage) T(std::move(*other));
            m_HasValue = true;
            other.Destroy();
        }

        return *this;
    }

    /// @brief Checks if the `Optional` contains a value.
    /// @return `true` if the `Optional` contains a value, `false` otherwise.
    inline bool HasValue() const { return m_HasValue; }

    /// @brief Conversion to bool operator.
    /// @return `true` if the `Optional` contains a value, `false` otherwise.
    operator bool() const { return m_HasValue; }

    /// @brief Gets the stored value.
    ///
    /// This function triggers a breakpoint, only debug builds, if the `Optional` is empty.
    ///
    /// @return A reference to the stored value.
    T &Value()
    {
        XASSERT(m_HasValue);
        return *reinterpret_cast<T *>(&m_Storage);
    }

    /// @brief Gets the stored value (const version).
    ///
    /// This function triggers a breakpoint, only debug builds, if the `Optional` is empty.
    ///
    /// @return A const reference to the stored value.
    const T &Value() const
    {
        XASSERT(m_HasValue);
        return *reinterpret_cast<const T *>(&m_Storage);
    }

    /// @brief Gets the stored value or a default value if the `Optional` is empty.
    /// @param defaultValue The default value to return if the `Optional` is empty.
    /// @return The stored value if the `Optional` contains a value, `defaultValue` otherwise.
    T ValueOr(const T &defaultValue) const
    {
        return m_HasValue ? Value() : defaultValue;
    }

    /// @brief Gets the stored value or a default value if the `Optional` is empty.
    /// @param defaultValue The default value to return if the `Optional` is empty.
    /// @return The stored value if the `Optional` contains a value, `defaultValue` otherwise.
    T ValueOr(T &&defaultValue) const
    {
        return m_HasValue ? Value() : std::move(defaultValue);
    }

    /// @brief Gets the stored value.
    ///
    /// This function triggers a breakpoint, only debug builds, if the `Optional` is empty.
    ///
    /// @return A reference to the stored value.
    T &operator*()
    {
        XASSERT(m_HasValue);
        return *reinterpret_cast<T *>(&m_Storage);
    }

    /// @brief Gets the stored value (const version).
    ///
    /// This function triggers a breakpoint, only debug builds, if the `Optional` is empty.
    ///
    /// @return A const reference to the stored value.
    const T &operator*() const
    {
        XASSERT(m_HasValue);
        return *reinterpret_cast<const T *>(&m_Storage);
    }

private:
    // It would be much better to use a union type instead of a raw byte array but the
    // Xbox 360 compiler doesn't support unions of non-trivally copyable types like std::string
    typename std::aligned_storage<sizeof(T), __alignof(T)>::type m_Storage;
    bool m_HasValue;

    void Destroy()
    {
        if (m_HasValue)
        {
            reinterpret_cast<T *>(&m_Storage)->~T();
            m_HasValue = false;
        }
    }
};

}
