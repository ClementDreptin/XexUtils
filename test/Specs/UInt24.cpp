#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void UInt24()
{
    Describe("UInt24()");

    It("constructs a null UInt24", []() {
        XexUtils::UInt24 value;

        TEST_EQ(value, 0);
    });

    Describe("UInt24(uint32_t)");

    It("constructs a UInt24 from a uint32_t", []() {
        XexUtils::UInt24 value(3);

        TEST_EQ(value, 3);
    });

    It("constructs a UInt24 with the 24 bits of the input when it doesn't fit in 24 bits", []() {
        XexUtils::UInt24 value(0x3000123);

        TEST_EQ(value, 0x123);
    });

    Describe("UInt24(const uint8_t *)");

    It("construcs a UInt24 from an array of bytes", []() {
        const uint8_t bytes[] = { 0x12, 0x34, 0x56 };
        XexUtils::UInt24 value(bytes);

        TEST_EQ(value, 0x123456);
    });

    Describe("UInt24::operator=(uint32_t)");

    It("sets the internal data to the first 24 bits of the uint32_t", []() {
        XexUtils::UInt24 value(3);
        TEST_EQ(value, 3);

        value = 4;
        TEST_EQ(value, 4);
    });

    Describe("UInt24::AsUInt32()");

    It("converts the UInt24 into a uint32_t", []() {
        XexUtils::UInt24 value(3);

        uint32_t value32 = value.AsUInt32();
        TEST_EQ(value32, 3);
    });

    Describe("UInt24::operator+()");

    It("keeps the UInt24 intact", []() {
        XexUtils::UInt24 value(3);

        TEST_EQ(+value, 3);
    });

    Describe("UInt24::operator~()");

    It("bitflips a UInt24", []() {
        XexUtils::UInt24 value(3);

        TEST_EQ(~value, ~3 & 0xFFFFFF);
    });

    Describe("UInt24::operator++()");

    It("increments a UInt24", []() {
        XexUtils::UInt24 value(3);
        ++value;

        TEST_EQ(value, 4);
    });

    Describe("UInt24::operator++(int)");

    It("increments a UInt24", []() {
        XexUtils::UInt24 value(3);
        value++;

        TEST_EQ(value, 4);
    });

    Describe("UInt24::operator--()");

    It("decrements a UInt24", []() {
        XexUtils::UInt24 value(3);
        --value;

        TEST_EQ(value, 2);
    });

    Describe("UInt24::operator--(int)");

    It("decrements a UInt24", []() {
        XexUtils::UInt24 value(3);
        value--;

        TEST_EQ(value, 2);
    });

    Describe("UInt24::operator+=(const UInt24 &)");

    It("adds the other UInt24 to the current one", []() {
        XexUtils::UInt24 value(3);
        value += XexUtils::UInt24(4);
        value += 2;

        TEST_EQ(value, 9);
    });

    Describe("UInt24::operator-=(const UInt24 &)");

    It("substracts the other UInt24 from the current one", []() {
        XexUtils::UInt24 value(9);
        value -= XexUtils::UInt24(4);
        value -= 2;

        TEST_EQ(value, 3);
    });

    Describe("UInt24::operator*=(const UInt24 &)");

    It("multiplies the current UInt24 by the other one", []() {
        XexUtils::UInt24 value(3);
        value *= XexUtils::UInt24(4);
        value *= 2;

        TEST_EQ(value, 24);
    });

    Describe("UInt24::operator/=(const UInt24 &)");

    It("divides the current UInt24 by the other one", []() {
        XexUtils::UInt24 value(16);
        value /= XexUtils::UInt24(4);
        value /= 2;

        TEST_EQ(value, 2);
    });

    Describe("UInt24::operator%=(const UInt24 &)");

    It("computes the current UInt24 modulo the other one", []() {
        XexUtils::UInt24 value(14);
        value %= XexUtils::UInt24(5);
        value %= 2;

        TEST_EQ(value, 0);
    });

    Describe("UInt24::operator&=(const UInt24 &)");

    It("computes the bitwise AND of the current UInt24 and the other one", []() {
        XexUtils::UInt24 value(15);
        value &= XexUtils::UInt24(7);
        value &= 3;

        TEST_EQ(value, 3);
    });

    Describe("UInt24::operator|=(const UInt24 &)");

    It("computes the bitwise OR of the current UInt24 and the other one", []() {
        XexUtils::UInt24 value(8);
        value |= XexUtils::UInt24(4);
        value |= 2;

        TEST_EQ(value, 14);
    });

    Describe("UInt24::operator^=(const UInt24 &)");

    It("computes the bitwise XOR of the current UInt24 and the other one", []() {
        XexUtils::UInt24 value(10);
        value ^= XexUtils::UInt24(6);
        value ^= 3;

        TEST_EQ(value, 15);
    });

    Describe("UInt24::operator<<=(int)");

    It("shifts the current UInt24 left by the given number of bits", []() {
        XexUtils::UInt24 value(8);
        value <<= 3;

        TEST_EQ(value, 64);
    });

    Describe("UInt24::operator>>=(int)");

    It("shifts the current UInt24 right by the given number of bits", []() {
        XexUtils::UInt24 value(64);
        value >>= 3;

        TEST_EQ(value, 8);
    });

    Describe("operator+(UInt24 a, const UInt24 &b)");

    It("adds a and b together", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(3) + XexUtils::UInt24(4);

        TEST_EQ(value, 7);
    });

    Describe("operator-(UInt24 a, const UInt24 &b)");

    It("substracts b from a", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(4) - XexUtils::UInt24(3);

        TEST_EQ(value, 1);
    });

    Describe("operator*(UInt24 a, const UInt24 &b)");

    It("multiplies a by b", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(3) * XexUtils::UInt24(4);

        TEST_EQ(value, 12);
    });

    Describe("operator/(UInt24 a, const UInt24 &b)");

    It("divides a by b", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(12) / XexUtils::UInt24(4);

        TEST_EQ(value, 3);
    });

    Describe("operator%(UInt24 a, const UInt24 &b)");

    It("computes a modulo b", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(9) % XexUtils::UInt24(4);

        TEST_EQ(value, 1);
    });

    Describe("operator&(UInt24 a, const UInt24 &b)");

    It("computes the bitwise AND of a and b", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(12) & XexUtils::UInt24(4);

        TEST_EQ(value, 4);
    });

    Describe("operator|(UInt24 a, const UInt24 &b)");

    It("computes the bitwise OR of a and b", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(16) | XexUtils::UInt24(4);

        TEST_EQ(value, 20);
    });

    Describe("operator|(UInt24 a, const UInt24 &b)");

    It("computes the bitwise XOR of a and b", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(12) ^ XexUtils::UInt24(4);

        TEST_EQ(value, 8);
    });

    Describe("operator<<(UInt24 a, int)");

    It("shifts a left by the given number of bits", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(8) << 2;

        TEST_EQ(value, 32);
    });

    Describe("operator>>(UInt24 a, int)");

    It("shifts a right by the given number of bits", []() {
        XexUtils::UInt24 value = XexUtils::UInt24(8) >> 2;

        TEST_EQ(value, 2);
    });

    Describe("operator==(const UInt24 &a, const UInt24 &b)");

    It("returns true if a and b are equal, false otherwise", []() {
        bool equal = XexUtils::UInt24(3) == XexUtils::UInt24(3);
        bool notEqual = XexUtils::UInt24(3) == XexUtils::UInt24(4);

        TEST_EQ(equal, true);
        TEST_EQ(notEqual, false);
    });

    Describe("operator!=(const UInt24 &a, const UInt24 &b)");

    It("returns true if a and b are different, false otherwise", []() {
        bool different = XexUtils::UInt24(3) != 4;
        bool notDifferent = XexUtils::UInt24(3) != XexUtils::UInt24(3);

        TEST_EQ(different, true);
        TEST_EQ(notDifferent, false);
    });

    Describe("operator<(const UInt24 &a, const UInt24 &b)");

    It("returns true if a is less than b, false otherwise", []() {
        bool less = XexUtils::UInt24(3) < XexUtils::UInt24(4);
        bool notLess = XexUtils::UInt24(4) < XexUtils::UInt24(3);
        bool equal = XexUtils::UInt24(3) < XexUtils::UInt24(3);

        TEST_EQ(less, true);
        TEST_EQ(notLess, false);
        TEST_EQ(equal, false);
    });

    Describe("operator>(const UInt24 &a, const UInt24 &b)");

    It("returns true if a is greater than b, false otherwise", []() {
        bool greater = XexUtils::UInt24(4) > XexUtils::UInt24(3);
        bool notGreater = XexUtils::UInt24(3) > XexUtils::UInt24(4);
        bool equal = XexUtils::UInt24(3) > XexUtils::UInt24(3);

        TEST_EQ(greater, true);
        TEST_EQ(notGreater, false);
        TEST_EQ(equal, false);
    });

    Describe("operator<=(const UInt24 &a, const UInt24 &b)");

    It("returns true if a is less or equal to b, false otherwise", []() {
        bool less = XexUtils::UInt24(3) <= XexUtils::UInt24(4);
        bool notLess = XexUtils::UInt24(4) <= XexUtils::UInt24(3);
        bool equal = XexUtils::UInt24(3) <= XexUtils::UInt24(3);

        TEST_EQ(less, true);
        TEST_EQ(notLess, false);
        TEST_EQ(equal, true);
    });

    Describe("operator>=(const UInt24 &a, const UInt24 &b)");

    It("returns true if a is greater or equal to b, false otherwise", []() {
        bool greater = XexUtils::UInt24(4) >= XexUtils::UInt24(3);
        bool notGreater = XexUtils::UInt24(3) >= XexUtils::UInt24(4);
        bool equal = XexUtils::UInt24(3) >= XexUtils::UInt24(3);

        TEST_EQ(greater, true);
        TEST_EQ(notGreater, false);
        TEST_EQ(equal, true);
    });

    Describe("operator<<(std::ostream &, const UInt24 &)");

    It("writes the value's decimal representation to the output stream", []() {
        std::ostringstream os;
        os << XexUtils::UInt24(42);

        TEST_EQ(os.str(), "42");
    });

    Describe("operator>>(std::istream &, UInt24 &)");

    It("reads a decimal value from the input stream into the UInt24", []() {
        std::istringstream is("3");
        XexUtils::UInt24 value;
        is >> value;

        TEST_EQ(value, 3);
    });

    It("leaves the value unchanged and sets the fail bit on malformed input", []() {
        XexUtils::UInt24 value(3);
        std::istringstream is("not_a_number");
        is >> value;

        TEST_EQ(value, 3);
        TEST_EQ(is.fail(), true);
    });
}
