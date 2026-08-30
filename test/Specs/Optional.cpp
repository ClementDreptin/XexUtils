#include <string>
#include <utility>
#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Optional()
{
    Describe("Optional<T>::Optional()");

    It("constructs an empty Optional", []() {
        auto opt = XexUtils::Optional<int>();
        TEST_EQ(opt.HasValue(), false);
    });

    Describe("Optional<T>::Optional(const T &)");

    It("constructs a valid Optional from a value", []() {
        int value = 3;
        auto opt = XexUtils::Optional<int>(value);
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), 3);
    });

    Describe("Optional<T>::Optional(T &&)");

    It("constructs a valid Optional from an rvalue reference", []() {
        std::string str = "some text";
        auto opt = XexUtils::Optional<std::string>(std::move(str));
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), "some text");
        TEST_EQ(str.size(), 0);
    });

    Describe("Optional<T>::Optional(NullOpt)");

    It("constructs an empty Optional from a NullOpt", []() {
        auto opt = XexUtils::Optional<int>(NullOpt());
        TEST_EQ(opt.HasValue(), false);
    });

    Describe("Optional<T>::Optional(const Optional &)");

    It("doesn't do anything when copying A into B if A is empty", []() {
        auto A = XexUtils::Optional<int>();
        auto B(A);
        TEST_EQ(B.HasValue(), false);
    });

    It("copies A into B when A is valid", []() {
        auto A = XexUtils::Optional<int>(3);
        auto B(A);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
    });

    Describe("Optional<T>::Optional(Optional &&other)");

    It("doesn't do anything when moving A into B if A is empty", []() {
        auto A = XexUtils::Optional<int>();
        auto B(std::move(A));
        TEST_EQ(B.HasValue(), false);
    });

    It("moves A into B when A is valid", []() {
        auto A = XexUtils::Optional<int>(3);
        auto B(std::move(A));
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
        TEST_EQ(A.HasValue(), false);
    });

    Describe("Optional<T>::operator=(const T &)");

    It("sets the Optional to the value when it already has a value", []() {
        auto opt = XexUtils::Optional<int>(3);
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), 3);
        int value = 4;
        opt = value;
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), value);
    });

    It("sets the Optional to the value when it's empty", []() {
        auto opt = XexUtils::Optional<int>();
        TEST_EQ(opt.HasValue(), false);
        int value = 4;
        opt = value;
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), value);
    });

    Describe("Optional<T>::operator=(T &&)");

    It("moves the value into the Optional when it already has a value", []() {
        std::string str = "new text";
        auto opt = XexUtils::Optional<std::string>("initial text");
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), "initial text");
        opt = std::move(str);
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), "new text");
        TEST_EQ(str.size(), 0);
    });

    It("moves the value into the Optional when it's empty", []() {
        std::string str = "some text";
        auto opt = XexUtils::Optional<std::string>();
        TEST_EQ(opt.HasValue(), false);
        opt = std::move(str);
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), "some text");
        TEST_EQ(str.size(), 0);
    });

    Describe("Optional<T>::operator=(NullOpt)");

    It("destroys the Optional", []() {
        auto opt = XexUtils::Optional<int>(3);
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), 3);
        opt = NullOpt();
        TEST_EQ(opt.HasValue(), false);
    });

    Describe("Optional<T>::operator=(const Optional &)");

    It("doesn't do anything when assigning an Optional to itself", []() {
        auto opt = XexUtils::Optional<int>(3);
        opt = opt;
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), 3);
    });

    It("doesn't do anything if both A and B are empty", []() {
        auto A = XexUtils::Optional<int>();
        auto B = XexUtils::Optional<int>();
        TEST_EQ(A.HasValue(), false);
        TEST_EQ(B.HasValue(), false);
        B = A;
        TEST_EQ(A.HasValue(), false);
        TEST_EQ(B.HasValue(), false);
    });

    It("copies A into B if both A and B are valid", []() {
        auto A = XexUtils::Optional<int>(3);
        auto B = XexUtils::Optional<int>(4);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 4);
        B = A;
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
    });

    It("copies A into B if A is valid and B is empty", []() {
        auto A = XexUtils::Optional<int>(3);
        auto B = XexUtils::Optional<int>();
        TEST_EQ(B.HasValue(), false);
        B = A;
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
    });

    It("destroys B if A is empty and B is valid", []() {
        auto A = XexUtils::Optional<int>();
        auto B = XexUtils::Optional<int>(3);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
        B = A;
        TEST_EQ(B.HasValue(), false);
    });

    Describe("Optional<T>::operator=(Optional &&)");

    It("doesn't do anything when moving an Optional to itself", []() {
        auto opt = XexUtils::Optional<int>(3);
        opt = std::move(opt);
        TEST_EQ(opt.HasValue(), true);
        TEST_EQ(opt.Value(), 3);
    });

    It("doesn't do anything if both A and B are empty", []() {
        auto A = XexUtils::Optional<int>();
        auto B = XexUtils::Optional<int>();
        TEST_EQ(A.HasValue(), false);
        TEST_EQ(B.HasValue(), false);
        B = std::move(A);
        TEST_EQ(A.HasValue(), false);
        TEST_EQ(B.HasValue(), false);
    });

    It("moves A into B if both A and B are valid", []() {
        auto A = XexUtils::Optional<int>(3);
        auto B = XexUtils::Optional<int>(4);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 4);
        B = std::move(A);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
        TEST_EQ(A.HasValue(), false);
    });

    It("moves A into B if A is valid and B is empty", []() {
        auto A = XexUtils::Optional<int>(3);
        auto B = XexUtils::Optional<int>();
        TEST_EQ(B.HasValue(), false);
        B = std::move(A);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
        TEST_EQ(A.HasValue(), false);
    });

    It("destroys B if A is empty and B is valid", []() {
        auto A = XexUtils::Optional<int>();
        auto B = XexUtils::Optional<int>(3);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
        B = std::move(A);
        TEST_EQ(B.HasValue(), false);
    });

    Describe("Optional<T>::HasValue()");

    It("returns true when the Optional is valid", []() {
        auto opt = XexUtils::Optional<int>(3);
        bool valid = opt.HasValue();
        TEST_EQ(valid, true);
    });

    It("returns false when the Optional is empty", []() {
        auto opt = XexUtils::Optional<int>();
        bool valid = opt.HasValue();
        TEST_EQ(valid, false);
    });

    Describe("Optional<T>::operator bool()");

    It("returns true when the Optional is valid", []() {
        auto opt = XexUtils::Optional<int>(3);
        bool valid = opt;
        TEST_EQ(valid, true);
    });

    It("returns false when the Optional is empty", []() {
        auto opt = XexUtils::Optional<int>();
        bool valid = opt;
        TEST_EQ(valid, false);
    });

    Describe("Optional<T>::Value()");

    It("returns the value", []() {
        auto opt = XexUtils::Optional<int>(3);
        TEST_EQ(opt.Value(), 3);
    });

    Describe("Optional<T>::operator*()");

    It("returns the value", []() {
        auto opt = XexUtils::Optional<int>(3);
        TEST_EQ(*opt, 3);
    });

    Describe("Optional<T>::operator->()");

    It("returns a pointer to the value", []() {
        auto opt = XexUtils::Optional<std::string>("some text");
        TEST_EQ(opt->size(), 9);
    });

    Describe("Optional<T>::ValueOr(const T &)");

    It("returns the value when the Optional is valid", []() {
        auto opt = XexUtils::Optional<int>(3);
        int defaultValue = 4;
        int value = opt.ValueOr(defaultValue);
        TEST_EQ(value, 3);
    });

    It("returns the default value when the Optional is empty", []() {
        auto opt = XexUtils::Optional<int>();
        int defaultValue = 4;
        int value = opt.ValueOr(defaultValue);
        TEST_EQ(value, 4);
    });

    Describe("Optional<T>::ValueOr(T &&)");

    It("returns the value when the Optional is valid", []() {
        auto opt = XexUtils::Optional<std::string>("some text");
        std::string defaultValue = "some default text";
        std::string value = opt.ValueOr(std::move(defaultValue));
        TEST_EQ(value, "some text");
    });

    It("returns the default value when the Optional is empty", []() {
        auto opt = XexUtils::Optional<std::string>();
        std::string defaultValue = "some default text";
        std::string value = opt.ValueOr(std::move(defaultValue));
        TEST_EQ(value, "some default text");
        TEST_EQ(defaultValue.size(), 0);
    });
}
