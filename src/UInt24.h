#pragma once

namespace XexUtils
{

/// @brief A class to represent to 24-bit unsigned integer.
class UInt24
{
public:
    /// @brief Creates an empty `UInt24` (initialized to 0).
    UInt24();

    /// @brief Creates a `UInt24` from a `uint32_t`.
    /// @param value The `uint32_t`.
    UInt24(uint32_t value);

    /// @brief Creates a `UInt24` from a byte array.
    /// @param bytes The byte array.
    UInt24(const uint8_t (&bytes)[3]);

    /// @brief Assigns a `uint32_t` to the `UInt24`.
    /// @param value The `uint32_t`.
    /// @return The current `UInt24`.
    UInt24 &operator=(uint32_t value);

    /// @brief Assigns the content of a byte array to the `UInt24`.
    /// @param bytes The byte array.
    /// @return The current `UInt24`.
    UInt24 &operator=(const uint8_t (&bytes)[3]);

    /// @brief Converts the `UInt24` to a `uint32_t`.
    /// @return A `uint32_t`.
    uint32_t AsUInt32() const;

    /// @brief Returns the current `UInt24` unchanged.
    /// @return A copy of the current `UInt24`.
    UInt24 operator+() const;

    /// @brief Computes the bitwise complement of the `UInt24`.
    /// @return A new `UInt24` with every bit inverted.
    UInt24 operator~() const;

    /// @brief Increments the `UInt24` by 1 (pre-increment).
    /// @return The current `UInt24`, after incrementing.
    UInt24 &operator++();

    /// @brief Increments the `UInt24` by 1 (post-increment).
    /// @return A copy of the `UInt24`, before incrementing.
    UInt24 operator++(int);

    /// @brief Decrements the `UInt24` by 1 (pre-decrement).
    /// @return The current `UInt24`, after decrementing.
    UInt24 &operator--();

    /// @brief Decrements the `UInt24` by 1 (post-decrement).
    /// @return A copy of the `UInt24`, before decrementing.
    UInt24 operator--(int);

    /// @brief Adds another `UInt24` to the current one.
    /// @param other The `UInt24` to add.
    /// @return The current `UInt24`, after adding.
    UInt24 &operator+=(const UInt24 &other);

    /// @brief Subtracts another `UInt24` from the current one.
    /// @param other The `UInt24` to subtract.
    /// @return The current `UInt24`, after subtracting.
    UInt24 &operator-=(const UInt24 &other);

    /// @brief Multiplies the current `UInt24` by another one.
    /// @param other The `UInt24` to multiply by.
    /// @return The current `UInt24`, after multiplying.
    UInt24 &operator*=(const UInt24 &other);

    /// @brief Divides the current `UInt24` by another one.
    /// @param other The `UInt24` to divide by.
    /// @return The current `UInt24`, after dividing.
    UInt24 &operator/=(const UInt24 &other);

    /// @brief Computes the current `UInt24` modulo the other one.
    /// @param other The `UInt24` to divide by.
    /// @return The current `UInt24`, after taking the remainder.
    UInt24 &operator%=(const UInt24 &other);

    /// @brief Computes the bitwise AND of the current `UInt24` and another one.
    /// @param other The `UInt24` to AND with.
    /// @return The current `UInt24`, after the operation.
    UInt24 &operator&=(const UInt24 &other);

    /// @brief Computes the bitwise OR of the current `UInt24` and another one.
    /// @param other The `UInt24` to OR with.
    /// @return The current `UInt24`, after the operation.
    UInt24 &operator|=(const UInt24 &other);

    /// @brief Computes the bitwise XOR of the current `UInt24` and another one.
    /// @param other The `UInt24` to XOR with.
    /// @return The current `UInt24`, after the operation.
    UInt24 &operator^=(const UInt24 &other);

    /// @brief Shifts the current `UInt24` left by a given number of bits.
    /// @param shift The number of bits to shift by.
    /// @return The current `UInt24`, after shifting.
    UInt24 &operator<<=(int shift);

    /// @brief Shifts the current `UInt24` right by a given number of bits.
    /// @param shift The number of bits to shift by.
    /// @return The current `UInt24`, after shifting.
    UInt24 &operator>>=(int shift);

private:
    uint8_t m_Data[3];

private:
    void Assign(uint32_t value);
};

/// @brief Adds two `UInt24`s together.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return The sum of `a` and `b`.
UInt24 operator+(UInt24 a, const UInt24 &b);

/// @brief Subtracts one `UInt24` from another.
/// @param a The `UInt24` to subtract from.
/// @param b The `UInt24` to subtract.
/// @return The difference between `a` and `b`.
UInt24 operator-(UInt24 a, const UInt24 &b);

/// @brief Multiplies two `UInt24`s together.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return The product of `a` and `b`.
UInt24 operator*(UInt24 a, const UInt24 &b);

/// @brief Divides one `UInt24` by another.
/// @param a The `UInt24` to divide.
/// @param b The `UInt24` to divide by.
/// @return The quotient of `a` divided by `b`.
UInt24 operator/(UInt24 a, const UInt24 &b);

/// @brief Computes one `UInt24` modulo another.
/// @param a The `UInt24` to divide.
/// @param b The `UInt24` to divide by.
/// @return The remainder of `a` divided by `b`.
UInt24 operator%(UInt24 a, const UInt24 &b);

/// @brief Computes the bitwise AND of two `UInt24`s.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return The bitwise AND of `a` and `b`.
UInt24 operator&(UInt24 a, const UInt24 &b);

/// @brief Computes the bitwise OR of two `UInt24`s.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return The bitwise OR of `a` and `b`.
UInt24 operator|(UInt24 a, const UInt24 &b);

/// @brief Computes the bitwise XOR of two `UInt24`s.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return The bitwise XOR of `a` and `b`.
UInt24 operator^(UInt24 a, const UInt24 &b);

/// @brief Shifts a `UInt24` left by a given number of bits.
/// @param a The `UInt24` to shift.
/// @param shift The number of bits to shift by.
/// @return `a`, shifted left by `shift` bits.
UInt24 operator<<(UInt24 a, int shift);

/// @brief Shifts a `UInt24` right by a given number of bits.
/// @param a The `UInt24` to shift.
/// @param shift The number of bits to shift by.
/// @return `a`, shifted right by `shift` bits.
UInt24 operator>>(UInt24 a, int shift);

/// @brief Checks whether two `UInt24`s are equal.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return `true` if `a` and `b` are equal, `false` otherwise.
bool operator==(const UInt24 &a, const UInt24 &b);

/// @brief Checks whether two `UInt24`s are different.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return `true` if `a` and `b` are different, `false` otherwise.
bool operator!=(const UInt24 &a, const UInt24 &b);

/// @brief Checks whether a `UInt24` is less than another.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return `true` if `a` is less than `b`, `false` otherwise.
bool operator<(const UInt24 &a, const UInt24 &b);

/// @brief Checks whether a `UInt24` is greater than another.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return `true` if `a` is greater than `b`, `false` otherwise.
bool operator>(const UInt24 &a, const UInt24 &b);

/// @brief Checks whether a `UInt24` is less than or equal to another.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return `true` if `a` is less than or equal to `b`, `false` otherwise.
bool operator<=(const UInt24 &a, const UInt24 &b);

/// @brief Checks whether a `UInt24` is greater than or equal to another.
/// @param a The first `UInt24`.
/// @param b The second `UInt24`.
/// @return `true` if `a` is greater than or equal to `b`, `false` otherwise.
bool operator>=(const UInt24 &a, const UInt24 &b);

/// @brief Writes a `UInt24`'s decimal representation to an output stream.
/// @param os The output stream to write to.
/// @param value The `UInt24` to write.
/// @return The output stream, after writing.
std::ostream &operator<<(std::ostream &os, const UInt24 &value);

/// @brief Reads a decimal value from an input stream into a `UInt24`.
/// @param is The input stream to read from.
/// @param value The `UInt24` to read into.
/// @return The input stream, after reading.
std::istream &operator>>(std::istream &is, UInt24 &value);

static_assert(sizeof(UInt24) == 3, "UInt24 must be exactly 3 bytes.");

}
