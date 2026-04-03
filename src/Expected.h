#pragma once

namespace XexUtils
{

/// @brief A class that tags a value as an error, used to create an `Expected` in the error state.
/// @tparam E The error type.
template<typename E>
class Unexpected
{
public:
    /// @brief Creates an `Unexpected` from an error.
    /// @param error The error.
    Unexpected(const E &error)
        : m_Error(error)
    {
    }

    /// @brief Creates an `Unexpected` from an rvalue reference to an error.
    /// @param error The rvalue reference to an error.
    Unexpected(E &&error)
        : m_Error(std::move(error))
    {
    }

    /// @brief Returns the stored error.
    /// @return A reference to the stored error.
    inline E &Error() { return m_Error; }

    /// @brief Returns the stored error (const version).
    /// @return A const reference to the stored error.
    inline const E &Error() const { return m_Error; }

private:
    E m_Error;
};

/// @brief A class to represent either a value of type `T` or an error of type `E`.
/// @tparam T The value type.
/// @tparam E The error type.
template<typename T, typename E>
class Expected
{
public:
    /// @brief Creates an `Expected` in a success state with a default-constructed value.
    Expected()
        : m_HasValue(true)
    {
        ConstructValue(T());
    }

    /// @brief Creates an `Expected` in a success state from a value.
    /// @param value The value.
    Expected(const T &value)
        : m_HasValue(true)
    {
        ConstructValue(value);
    }

    /// @brief Creates an `Expected` in a success state from an rvalue.
    /// @param value The rvalue.
    Expected(T &&value)
        : m_HasValue(true)
    {
        ConstructValue(std::move(value));
    }

    /// @brief Creates an `Expected` in an error state from an `Unexpected`.
    /// @param unexpected The `Unexpected` holding the error.
    Expected(const Unexpected<E> &unexpected)
        : m_HasValue(false)
    {
        ConstructError(unexpected.Error());
    }

    /// @brief Creates an `Expected` in an error state from an `Unexpected`.
    /// @param unexpected An rvalue reference to the `Unexpected` holding the error.
    Expected(Unexpected<E> &&unexpected)
        : m_HasValue(false)
    {
        ConstructError(std::move(unexpected.Error()));
    }

    /// @brief Copies `other` into the current `Expected`.
    /// @param other The `Expected` to copy.
    Expected(const Expected &other)
        : m_HasValue(other.m_HasValue)
    {
        if (m_HasValue)
            ConstructValue(other.Value());
        else
            ConstructError(other.Error());
    }

    /// @brief Moves `other` into the current `Expected`.
    /// @param other The `Expected` to move.
    Expected(Expected &&other)
        : m_HasValue(other.m_HasValue)
    {
        if (m_HasValue)
            ConstructValue(std::move(other.Value()));
        else
            ConstructError(std::move(other.Error()));
    }

    /// @brief Destroys the `Expected` and its value or error depending on the state.
    ~Expected()
    {
        Destroy();
    }

    /// @brief Assigns a value to the `Expected`, placing it in a success state.
    /// @param value The value.
    /// @return A reference to the `Expected`.
    Expected &operator=(const T &value)
    {
        Destroy();

        m_HasValue = true;
        ConstructValue(value);

        return *this;
    }

    /// @brief Moves a value into the `Expected`, placing it in a success state.
    /// @param value The value.
    /// @return A reference to the `Expected`.
    Expected &operator=(T &&value)
    {
        Destroy();

        m_HasValue = true;
        ConstructValue(std::move(value));

        return *this;
    }

    /// @brief Assigns an error from an `Unexpected` to the `Expected`, placing it in an error state.
    /// @param unexpected The `Unexpected` holding the error.
    /// @return A reference to the `Expected`.
    Expected &operator=(const Unexpected<E> &unexpected)
    {
        Destroy();

        m_HasValue = false;
        ConstructError(unexpected.Error());

        return *this;
    }

    /// @brief Moves an error from an `Unexpected` to the `Expected`, placing it in an error state.
    /// @param unexpected The `Unexpected` holding the error.
    /// @return A reference to the `Expected`.
    Expected &operator=(Unexpected<E> &&unexpected)
    {
        Destroy();

        m_HasValue = false;
        ConstructError(std::move(unexpected.Error()));

        return *this;
    }

    /// @brief Copies `other` with its state and value or error into another `Expected`.
    /// @param other The `Expected` to copy.
    /// @return A reference to the `Expected`.
    Expected &operator=(const Expected &other)
    {
        if (this == &other)
            return *this;

        Destroy();

        m_HasValue = other.m_HasValue;

        if (m_HasValue)
            ConstructValue(other.Value());
        else
            ConstructError(other.Error());

        return *this;
    }

    /// @brief Moves `other` with its state and value or error into another `Expected`.
    /// @param other The `Expected` to move.
    /// @return A reference to the `Expected`.
    Expected &operator=(Expected &&other)
    {
        if (this == &other)
            return *this;

        Destroy();

        m_HasValue = other.m_HasValue;

        if (m_HasValue)
            ConstructValue(std::move(other.Value()));
        else
            ConstructError(std::move(other.Error()));

        return *this;
    }

    /// @brief Checks if the `Expected` contains a value (success state).
    /// @return `true` if in the success state, `false` if in the error state.
    inline bool HasValue() const { return m_HasValue; }

    /// @brief Checks if the `Expected` contains a value (success state).
    /// @return `true` if in the success state, `false` if in the error state.
    operator bool() const { return m_HasValue; }

    /// @brief Gets the stored value.
    ///
    /// This function triggers a breakpoint, only in debug builds, if the `Expected` is in an error state.
    ///
    /// @return A reference to the stored value.
    T &Value()
    {
        XASSERT(m_HasValue);
        return *reinterpret_cast<T *>(&m_Storage);
    }

    /// @brief Gets the stored value (const version).
    ///
    /// This function triggers a breakpoint, only in debug builds, if the `Expected` is in an error state.
    ///
    /// @return A const reference to the stored value.
    const T &Value() const
    {
        XASSERT(m_HasValue);
        return *reinterpret_cast<const T *>(&m_Storage);
    }

    /// @brief Gets the stored value.
    ///
    /// This function triggers a breakpoint, only in debug builds, if the `Expected` is in an error state.
    ///
    /// @return A reference to the stored value.
    T &operator*()
    {
        return Value();
    }

    /// @brief Gets the stored value (const version).
    ///
    /// This function triggers a breakpoint, only in debug builds, if the `Expected` is in an error state.
    ///
    /// @return A const reference to the stored value.
    const T &operator*() const
    {
        return Value();
    }

    /// @brief Gets the stored value, or `defaultValue` if the `Expected` is in an error state.
    /// @param defaultValue The default value to return if the `Expected` is in an error state.
    /// @return The stored value if the `Expected` is in a success state, `defaultValue` otherwise.
    T ValueOr(const T &defaultValue) const
    {
        return m_HasValue ? Value() : defaultValue;
    }

    /// @brief Gets the stored value, or `defaultValue` if the `Expected` is in an error state.
    /// @param defaultValue The default value to return if the `Expected` is in an error state.
    /// @return The stored value if the `Expected` is in a success state, `defaultValue` otherwise.
    T ValueOr(T &&defaultValue) const
    {
        return m_HasValue ? Value() : std::move(defaultValue);
    }

    /// @brief Gets the stored error.
    ///
    /// This function triggers a breakpoint, only in debug builds, if the `Expected` is in a success state.
    ///
    /// @return A reference to the stored error.
    E &Error()
    {
        XASSERT(!m_HasValue);
        return *reinterpret_cast<E *>(&m_Storage);
    }

    /// @brief Gets the stored error (const version).
    ///
    /// This function triggers a breakpoint, only in debug builds, if the `Expected` is in a success state.
    ///
    /// @return A const reference to the stored error.
    const E &Error() const
    {
        XASSERT(!m_HasValue);
        return *reinterpret_cast<const E *>(&m_Storage);
    }

    /// @brief Gets the stored error, or `defaultError` if the `Expected` is in a success state.
    /// @param defaultError The default error to return if the `Expected` is in a success state.
    /// @return The stored error if the `Expected` is in an error state, `defaultError` otherwise.
    E ErrorOr(const E &defaultError) const
    {
        return !m_HasValue ? Error() : defaultError;
    }

    /// @brief Gets the stored error, or `defaultError` if the `Expected` is in a success state.
    /// @param defaultError The default error to return if the `Expected` is in a success state.
    /// @return The stored error if the `Expected` is in an error state, `defaultError` otherwise.
    E ErrorOr(E &&defaultError) const
    {
        return !m_HasValue ? Error() : std::move(defaultError);
    }

private:
    // It would be much better to use a union type instead of a raw byte array but the
    // Xbox 360 compiler doesn't support unions of non-trivally copyable types like std::string
    typename std::aligned_storage<(sizeof(T) > sizeof(E) ? sizeof(T) : sizeof(E)), (__alignof(T) > __alignof(E) ? __alignof(T) : __alignof(E))>::type m_Storage;
    bool m_HasValue;

    void ConstructValue(const T &value)
    {
        new (&m_Storage) T(value);
    }

    void ConstructValue(T &&value)
    {
        new (&m_Storage) T(std::move(value));
    }

    void ConstructError(const E &error)
    {
        new (&m_Storage) E(error);
    }

    void ConstructError(E &&error)
    {
        new (&m_Storage) E(std::move(error));
    }

    void Destroy()
    {
        if (m_HasValue)
            Value().~T();
        else
            Error().~E();
    }
};

}
