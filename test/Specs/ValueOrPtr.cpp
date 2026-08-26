#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void ValueOrPtr()
{
    Describe("ValueOrPtr<T>::ValueOrPtr(const T &)");

    It("creates a ValueOrPtr from a value", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(3);

        TEST_EQ(valueOrPtr, 3);
    });

    Describe("ValueOrPtr<T>::ValueOrPtr(T &&)");

    It("creates a ValueOrPtr from a moved value", []() {
        std::string value = "hello";
        XexUtils::ValueOrPtr<std::string> valueOrPtr(std::move(value));

        TEST_EQ(*valueOrPtr, "hello");
        TEST_EQ(value.size(), 0);
    });

    Describe("ValueOrPtr<T>::ValueOrPtr(T *)");

    It("creates a ValueOrPtr from a pointer", []() {
        int value = 3;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        TEST_EQ(valueOrPtr, 3);
    });

    It("reflects changes made through the original pointer", []() {
        int value = 3;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        value = 42;

        TEST_EQ(valueOrPtr, 42);
    });

    Describe("ValueOrPtr<T>::ValueOrPtr(const ValueOrPtr<T> &)");

    It("copies the value when the source is in value mode", []() {
        XexUtils::ValueOrPtr<int> src(42);
        XexUtils::ValueOrPtr<int> copy(src);

        TEST_EQ(*src, 42);
        TEST_EQ(*copy, 42);
    });

    It("aliases the same pointer when the source is in pointer mode", []() {
        int value = 42;
        XexUtils::ValueOrPtr<int> src(&value);
        XexUtils::ValueOrPtr<int> copy(src);

        TEST_EQ(*copy, 42);
        TEST_EQ(&copy, &value);

        *copy = 7;
        TEST_EQ(*src, 7);
        TEST_EQ(value, 7);
    });

    Describe("ValueOrPtr<T>::ValueOrPtr(ValueOrPtr<T> &&)");

    It("leaves the source's value in a moved-from state after moving a value", []() {
        XexUtils::ValueOrPtr<std::string> src("hello");
        XexUtils::ValueOrPtr<std::string> moved(std::move(src));

        TEST_EQ(*moved, "hello");
        TEST_EQ(src->size(), 0);
    });

    It("aliases the same pointer when the source is in pointer mode, without touching the pointee", []() {
        std::string value("hello");
        XexUtils::ValueOrPtr<std::string> src(&value);
        XexUtils::ValueOrPtr<std::string> moved(std::move(src));

        TEST_EQ(*moved, "hello");
        TEST_EQ(&moved, &value);

        *moved = "modified";
        TEST_EQ(value, "modified");
    });

    Describe("ValueOrPtr<T>::operator=(const ValueOrPtr<T> &)");

    It("copies the value when the source is in value mode", []() {
        XexUtils::ValueOrPtr<int> src(42);
        XexUtils::ValueOrPtr<int> copy = src;

        TEST_EQ(*src, 42);
        TEST_EQ(*copy, 42);
    });

    It("aliases the same pointer when the source is in pointer mode", []() {
        int value = 42;
        XexUtils::ValueOrPtr<int> src(&value);
        XexUtils::ValueOrPtr<int> copy = src;

        TEST_EQ(*copy, 42);
        TEST_EQ(&copy, &value);

        *copy = 7;
        TEST_EQ(*src, 7);
        TEST_EQ(value, 7);
    });

    Describe("ValueOrPtr<T>::operator=(ValueOrPtr<T> &&)");

    It("leaves the source's value in a moved-from state after moving a value", []() {
        XexUtils::ValueOrPtr<std::string> src("hello");
        XexUtils::ValueOrPtr<std::string> moved = std::move(src);

        TEST_EQ(*moved, "hello");
        TEST_EQ(src->size(), 0);
    });

    It("aliases the same pointer when the source is in pointer mode, without touching the pointee", []() {
        std::string value("hello");
        XexUtils::ValueOrPtr<std::string> src(&value);
        XexUtils::ValueOrPtr<std::string> moved = std::move(src);

        TEST_EQ(*moved, "hello");
        TEST_EQ(&moved, &value);

        *moved = "modified";
        TEST_EQ(value, "modified");
    });

    Describe("ValueOrPtr<T>::operator*() const");

    It("dereferences to the value when constructed from a value", []() {
        const XexUtils::ValueOrPtr<int> valueOrPtr(3);

        TEST_EQ(*valueOrPtr, 3);
    });

    It("dereferences to the pointee when constructed from a pointer", []() {
        int value = 3;
        const XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        TEST_EQ(*valueOrPtr, 3);
    });

    Describe("ValueOrPtr<T>::operator*()");

    It("allows mutating the stored value directly", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(3);

        *valueOrPtr = 42;

        TEST_EQ(valueOrPtr, 42);
    });

    It("allows mutating the pointee directly, writing through to the original", []() {
        int value = 3;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        *valueOrPtr = 42;

        TEST_EQ(value, 42);
    });

    Describe("ValueOrPtr<T>::operator&() const");

    It("returns the address of the internal value when in value mode", []() {
        const XexUtils::ValueOrPtr<int> valueOrPtr(3);

        TEST_EQ(*(&valueOrPtr), 3);
    });

    It("returns the original pointer when in pointer mode", []() {
        int value = 3;
        const XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        TEST_EQ(&valueOrPtr, &value);
    });

    Describe("ValueOrPtr<T>::operator&()");

    It("returns a writable address of the internal value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(3);

        *(&valueOrPtr) = 42;

        TEST_EQ(valueOrPtr, 42);
    });

    It("returns the original writable pointer in pointer mode", []() {
        int value = 3;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        *(&valueOrPtr) = 42;

        TEST_EQ(value, 42);
    });

    Describe("ValueOrPtr<T>::operator->() const");

    It("dereferences to the value when in value mode", []() {
        const XexUtils::ValueOrPtr<int> valueOrPtr(3);

        TEST_EQ(*valueOrPtr.operator->(), 3);
    });

    It("dereferences to the pointee when in pointer mode", []() {
        int value = 3;
        const XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        TEST_EQ(valueOrPtr.operator->(), &value);
    });

    Describe("ValueOrPtr<T>::operator->()");

    It("allows mutating the value through the returned pointer", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(3);

        *valueOrPtr.operator->() = 42;

        TEST_EQ(valueOrPtr, 42);
    });

    It("writes through to the pointee in pointer mode", []() {
        int value = 3;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        *valueOrPtr.operator->() = 42;

        TEST_EQ(value, 42);
    });

    Describe("ValueOrPtr<T>::operator T() const");

    It("implicitly converts to the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(3);

        int value = valueOrPtr;

        TEST_EQ(value, 3);
    });

    It("implicitly converts to the pointee's value in pointer mode", []() {
        int value = 3;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        int converted = valueOrPtr;

        TEST_EQ(converted, 3);
    });

    Describe("ValueOrPtr<T>::operator-() const");

    It("negates the value in value mode", []() {
        const XexUtils::ValueOrPtr<int> valueOrPtr(12);

        TEST_EQ(-valueOrPtr, -12);
    });

    It("negates the pointee's value in pointer mode", []() {
        int value = 12;
        const XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        TEST_EQ(-valueOrPtr, -12);
    });

    Describe("ValueOrPtr<T>::operator+() const");

    It("returns the value unchanged in value mode", []() {
        const XexUtils::ValueOrPtr<int> valueOrPtr(12);

        TEST_EQ(+valueOrPtr, 12);
    });

    It("returns the pointee's value unchanged in pointer mode", []() {
        int value = 12;
        const XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        TEST_EQ(+valueOrPtr, 12);
    });

    Describe("ValueOrPtr<T>::operator~() const");

    It("returns the bitwise NOT of the value in value mode", []() {
        const XexUtils::ValueOrPtr<int> valueOrPtr(12);

        TEST_EQ(~valueOrPtr, ~12);
    });

    It("returns the bitwise NOT of the pointee's value in pointer mode", []() {
        int value = 12;
        const XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        TEST_EQ(~valueOrPtr, ~12);
    });

    Describe("ValueOrPtr<T>::operator+=(const T &)");

    It("adds to the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        valueOrPtr += 4;

        TEST_EQ(valueOrPtr, 14);
    });

    It("adds to the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr += 4;

        TEST_EQ(value, 14);
    });

    Describe("ValueOrPtr<T>::operator-=(const T &)");

    It("subtracts from the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        valueOrPtr -= 4;

        TEST_EQ(valueOrPtr, 6);
    });

    It("subtracts from the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr -= 4;

        TEST_EQ(value, 6);
    });

    Describe("ValueOrPtr<T>::operator*=(const T &)");

    It("multiplies the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        valueOrPtr *= 4;

        TEST_EQ(valueOrPtr, 40);
    });

    It("multiplies the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr *= 4;

        TEST_EQ(value, 40);
    });

    Describe("ValueOrPtr<T>::operator/=(const T &)");

    It("divides the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        valueOrPtr /= 4;

        TEST_EQ(valueOrPtr, 2);
    });

    It("divides the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr /= 4;

        TEST_EQ(value, 2);
    });

    Describe("ValueOrPtr<T>::operator%=(const T &)");

    It("takes the modulo of the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        valueOrPtr %= 4;

        TEST_EQ(valueOrPtr, 2);
    });

    It("takes the modulo of the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr %= 4;

        TEST_EQ(value, 2);
    });

    Describe("ValueOrPtr<T>::operator&=(const T &)");

    It("bitwise ANDs the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        valueOrPtr &= 6;

        TEST_EQ(valueOrPtr, 2);
    });

    It("bitwise ANDs the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr &= 6;

        TEST_EQ(value, 2);
    });

    Describe("ValueOrPtr<T>::operator|=(const T &)");

    It("bitwise ORs the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        valueOrPtr |= 4;

        TEST_EQ(valueOrPtr, 14);
    });

    It("bitwise ORs the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr |= 4;

        TEST_EQ(value, 14);
    });

    Describe("ValueOrPtr<T>::operator^=(const T &)");

    It("bitwise XORs the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        valueOrPtr ^= 6;

        TEST_EQ(valueOrPtr, 12);
    });

    It("bitwise XORs the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr ^= 6;

        TEST_EQ(value, 12);
    });

    Describe("ValueOrPtr<T>::operator<<=(const T &)");

    It("left shifts the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(3);

        valueOrPtr <<= 2;

        TEST_EQ(valueOrPtr, 12);
    });

    It("left shifts the pointee's value, writing through in pointer mode", []() {
        int value = 3;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr <<= 2;

        TEST_EQ(value, 12);
    });

    Describe("ValueOrPtr<T>::operator>>=(const T &)");

    It("right shifts the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(48);

        valueOrPtr >>= 2;

        TEST_EQ(valueOrPtr, 12);
    });

    It("right shifts the pointee's value, writing through in pointer mode", []() {
        int value = 48;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        valueOrPtr >>= 2;

        TEST_EQ(value, 12);
    });

    Describe("ValueOrPtr<T>::operator++()");

    It("pre-increments the value in value mode and returns a reference to itself", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        XexUtils::ValueOrPtr<int> &result = ++valueOrPtr;
        result = 42;

        TEST_EQ(valueOrPtr, 42);
    });

    It("pre-increments the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        ++valueOrPtr;

        TEST_EQ(value, 11);
    });

    Describe("ValueOrPtr<T>::operator++(int)");

    It("returns the value before incrementing, in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        XexUtils::ValueOrPtr<int> old = valueOrPtr++;

        TEST_EQ(old, 10);
        TEST_EQ(valueOrPtr, 11);
    });

    It("returns the pointee's value before incrementing, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        XexUtils::ValueOrPtr<int> old = valueOrPtr++;

        TEST_EQ(old, 10);
        TEST_EQ(value, 11);
    });

    Describe("ValueOrPtr<T>::operator--()");

    It("pre-decrements the value in value mode and returns a reference to itself", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        XexUtils::ValueOrPtr<int> &result = --valueOrPtr;
        result = 42;

        TEST_EQ(valueOrPtr, 42);
    });

    It("pre-decrements the pointee's value, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        --valueOrPtr;

        TEST_EQ(value, 9);
    });

    Describe("ValueOrPtr<T>::operator--(int)");

    It("returns the value before decrementing, in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(10);

        XexUtils::ValueOrPtr<int> old = valueOrPtr--;

        TEST_EQ(old, 10);
        TEST_EQ(valueOrPtr, 9);
    });

    It("returns the pointee's value before decrementing, writing through in pointer mode", []() {
        int value = 10;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);

        XexUtils::ValueOrPtr<int> old = valueOrPtr--;

        TEST_EQ(old, 10);
        TEST_EQ(value, 9);
    });

    Describe("operator+(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("adds two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs + rhs, 17);
    });

    It("adds two pointees' values in pointer mode", []() {
        int lhsValue = 12;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs + rhs, 17);
    });

    It("adds a value and a pointee's value in mixed mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs + rhs, 17);
    });

    Describe("operator-(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("subtracts two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs - rhs, 7);
    });

    It("subtracts two pointees' values in pointer mode", []() {
        int lhsValue = 12;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs - rhs, 7);
    });

    Describe("operator*(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("multiplies two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs * rhs, 60);
    });

    It("multiplies two pointees' values in pointer mode", []() {
        int lhsValue = 12;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs * rhs, 60);
    });

    Describe("operator/(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("divides two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs / rhs, 2);
    });

    It("divides two pointees' values in pointer mode", []() {
        int lhsValue = 12;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs / rhs, 2);
    });

    Describe("operator%(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("takes the modulo of two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12), rhs(5);

        TEST_EQ(lhs % rhs, 2);
    });

    It("takes the modulo of two pointees' values in pointer mode", []() {
        int lhsValue = 12;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs % rhs, 2);
    });

    Describe("operator&(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("bitwise ANDs two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs & rhs, 4);
    });

    It("bitwise ANDs two pointees' values in pointer mode", []() {
        int lhsValue = 12;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs & rhs, 4);
    });

    Describe("operator|(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("bitwise ORs two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs | rhs, 13);
    });

    It("bitwise ORs two pointees' values in pointer mode", []() {
        int lhsValue = 12;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs | rhs, 13);
    });

    Describe("operator^(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("bitwise XORs two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(12);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs ^ rhs, 9);
    });

    It("bitwise XORs two pointees' values in pointer mode", []() {
        int lhsValue = 12;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs ^ rhs, 9);
    });

    Describe("operator<<(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("left shifts two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(3);
        XexUtils::ValueOrPtr<int> rhs(2);

        TEST_EQ(lhs << rhs, 12);
    });

    It("left shifts two pointees' values in pointer mode", []() {
        int lhsValue = 3;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 2;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs << rhs, 12);
    });

    Describe("operator>>(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("right shifts two values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(48);
        XexUtils::ValueOrPtr<int> rhs(2);

        TEST_EQ(lhs >> rhs, 12);
    });

    It("right shifts two pointees' values in pointer mode", []() {
        int lhsValue = 48;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 2;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs >> rhs, 12);
    });

    Describe("operator==(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("returns true for equal values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs == rhs, true);
    });

    It("returns false for different values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(6);

        TEST_EQ(lhs == rhs, false);
    });

    It("compares pointees' values in pointer mode", []() {
        int lhsValue = 5;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs == rhs, true);
    });

    Describe("operator!=(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("returns false for equal values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs != rhs, false);
    });

    It("returns true for different values in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(6);

        TEST_EQ(lhs != rhs, true);
    });

    It("compares pointees' values in pointer mode", []() {
        int lhsValue = 5;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 6;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs != rhs, true);
    });

    Describe("operator<(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("returns true when the left value is smaller in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(6);

        TEST_EQ(lhs < rhs, true);
    });

    It("returns false when the left value is not smaller in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(6);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs < rhs, false);
    });

    It("compares pointees' values in pointer mode", []() {
        int lhsValue = 5;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 6;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs < rhs, true);
    });

    Describe("operator<=(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("returns true when the left value is smaller or equal in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs <= rhs, true);
    });

    It("returns false when the left value is greater in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(6);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs <= rhs, false);
    });

    It("compares pointees' values in pointer mode", []() {
        int lhsValue = 5;
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs <= rhs, true);
    });

    Describe("operator>(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("returns true when the left value is greater in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(6);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs > rhs, true);
    });

    It("returns false when the left value is not greater in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(6);

        TEST_EQ(lhs > rhs, false);
    });

    It("compares pointees' values in pointer mode", []() {
        int lhsValue = 6;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs > rhs, true);
    });

    Describe("operator>=(const ValueOrPtr<T> &, const ValueOrPtr<T> &)");

    It("returns true when the left value is greater or equal in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(5);

        TEST_EQ(lhs >= rhs, true);
    });

    It("returns false when the left value is smaller in value mode", []() {
        XexUtils::ValueOrPtr<int> lhs(5);
        XexUtils::ValueOrPtr<int> rhs(6);

        TEST_EQ(lhs >= rhs, false);
    });

    It("compares pointees' values in pointer mode", []() {
        int lhsValue = 5;
        XexUtils::ValueOrPtr<int> lhs(&lhsValue);
        int rhsValue = 5;
        XexUtils::ValueOrPtr<int> rhs(&rhsValue);

        TEST_EQ(lhs >= rhs, true);
    });

    Describe("operator<<(std::ostream &, const ValueOrPtr<T> &)");

    It("streams the value in value mode", []() {
        XexUtils::ValueOrPtr<int> valueOrPtr(3);
        std::ostringstream stream;

        stream << valueOrPtr;

        TEST_EQ(stream.str(), "3");
    });

    It("streams the pointee's value in pointer mode", []() {
        int value = 3;
        XexUtils::ValueOrPtr<int> valueOrPtr(&value);
        std::ostringstream stream;

        stream << valueOrPtr;

        TEST_EQ(stream.str(), "3");
    });
}
