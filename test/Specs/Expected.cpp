#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Expected()
{
    Describe("Unexpected(const E &)");

    It("constructs an Unexpected from an error", []() {
        std::string error = "error";
        auto unexp = XexUtils::Unexpected<std::string>(error);
        TEST_EQ(unexp.Error(), "error");
    });

    Describe("Unexpected(E &&)");

    It("constructs an Unexpected from an rvalue reference to an error", []() {
        std::string error = "error";
        auto unexp = XexUtils::Unexpected<std::string>(std::move(error));
        TEST_EQ(unexp.Error(), "error");
        TEST_EQ(error.size(), 0);
    });

    Describe("Expected()");

    It("constructs an Expected from the default value of the value type", []() {
        auto exp = XexUtils::Expected<int, std::string>();
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), int());
    });

    Describe("Expected(const T &)");

    It("constructs an Expected from a value", []() {
        int value = 3;
        auto exp = XexUtils::Expected<int, std::string>(value);
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), 3);
    });

    Describe("Expected(T &&)");

    It("constructs an Expected from an rvalue reference", []() {
        std::string value = "some text";
        auto exp = XexUtils::Expected<std::string, int>(std::move(value));
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), "some text");
        TEST_EQ(value.size(), 0);
    });

    Describe("Expected(const Unexpected<E> &)");

    It("constructs an Expected with an error from an Unexpected", []() {
        auto unexp = XexUtils::Unexpected<std::string>("error");
        auto exp = XexUtils::Expected<int, std::string>(unexp);
        TEST_EQ(exp.HasValue(), false);
        TEST_EQ(exp.Error(), "error");
    });

    Describe("Expected(Unexpected<E> &&)");

    It("constructs an Expected with an error from an Unexpected rvalue reference", []() {
        auto unexp = XexUtils::Unexpected<std::string>("error");
        auto exp = XexUtils::Expected<int, std::string>(std::move(unexp));
        TEST_EQ(exp.HasValue(), false);
        TEST_EQ(exp.Error(), "error");
        TEST_EQ(unexp.Error(), "");
    });

    Describe("Expected(const Expected &)");

    It("constructs an Expected with a value from an Expected with a value", []() {
        auto A = XexUtils::Expected<int, std::string>(3);
        auto B(A);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
    });

    It("constructs an Expected with an error from an Expected with an error", []() {
        auto A = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("error"));
        auto B(A);
        TEST_EQ(B.HasValue(), false);
        TEST_EQ(B.Error(), "error");
    });

    Describe("Expected(Expected &&)");

    It("constructs an Expected with a value from an rvalue reference to an Expected with a value", []() {
        auto A = XexUtils::Expected<int, std::string>(3);
        auto B(std::move(A));
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
    });

    It("constructs an Expected with an error from an rvalue reference to an Expected with an error", []() {
        auto A = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("error"));
        auto B(std::move(A));
        TEST_EQ(B.HasValue(), false);
        TEST_EQ(B.Error(), "error");
    });

    Describe("Expected::operator=(const T &)");

    It("sets the value of the Expected", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), 3);
        int value = 4;
        exp = value;
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), 4);
    });

    Describe("Expected::operator=(T &&)");

    It("sets the value of the Expected", []() {
        auto exp = XexUtils::Expected<std::string, int>("some text");
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), "some text");
        std::string otherText = "other text";
        exp = std::move(otherText);
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), "other text");
        TEST_EQ(otherText.size(), 0);
    });

    Describe("Expected::operator=(const Unexpected<E> &)");

    It("sets the error of the Expected to the error of the Unexpected", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), 3);
        auto unexp = XexUtils::Unexpected<std::string>("error");
        exp = unexp;
        TEST_EQ(exp.HasValue(), false);
        TEST_EQ(exp.Error(), "error");
    });

    Describe("Expected::operator=(Unexpected<E> &&)");

    It("sets the error of the Expected to the error of the Unexpected", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), 3);
        auto unexp = XexUtils::Unexpected<std::string>("error");
        exp = std::move(unexp);
        TEST_EQ(exp.HasValue(), false);
        TEST_EQ(exp.Error(), "error");
    });

    Describe("Expected::operator=(const Expected &)");

    It("doesn't do anything when assigning an Expected to itself", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        exp = exp;
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), 3);
    });

    It("copies the value of A into B if A has a value", []() {
        auto A = XexUtils::Expected<int, std::string>(3);
        auto B = XexUtils::Expected<int, std::string>(4);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 4);
        B = A;
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
    });

    It("copies the error of A into B if A has an error", []() {
        auto A = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("errorA"));
        auto B = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("errorB"));
        TEST_EQ(B.HasValue(), false);
        TEST_EQ(B.Error(), "errorB");
        B = A;
        TEST_EQ(B.HasValue(), false);
        TEST_EQ(B.Error(), "errorA");
    });

    Describe("Expected::operator=(Expected &&)");

    It("doesn't do anything when moving an Expected to itself", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        exp = std::move(exp);
        TEST_EQ(exp.HasValue(), true);
        TEST_EQ(exp.Value(), 3);
    });

    It("moves the value of A into B if A has a value", []() {
        auto A = XexUtils::Expected<int, std::string>(3);
        auto B = XexUtils::Expected<int, std::string>(4);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 4);
        B = std::move(A);
        TEST_EQ(B.HasValue(), true);
        TEST_EQ(B.Value(), 3);
    });

    It("moves the error of A into B if A has an error", []() {
        auto A = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("errorA"));
        auto B = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("errorB"));
        TEST_EQ(B.HasValue(), false);
        TEST_EQ(B.Error(), "errorB");
        B = std::move(A);
        TEST_EQ(B.HasValue(), false);
        TEST_EQ(B.Error(), "errorA");
    });

    Describe("Expected::operator bool()");

    It("returns true when the Expected has a value", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        bool hasValue = exp;
        TEST_EQ(hasValue, true);
    });

    It("returns false when the Expected has an error", []() {
        auto exp = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("error"));
        bool hasValue = exp;
        TEST_EQ(hasValue, false);
    });

    Describe("Expected::operator*()");

    It("returns the value", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        TEST_EQ(*exp, 3);
    });

    Describe("Expected::operator->()");

    It("returns a pointer to the value", []() {
        auto opt = XexUtils::Expected<std::string, int>("some text");
        TEST_EQ(opt->size(), 9);
    });

    Describe("Expected:ValueOr(const T &)");

    It("returns the value when the Expected has a value", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        int defaultValue = 4;
        int value = exp.ValueOr(defaultValue);
        TEST_EQ(value, 3);
    });

    It("returns the default value when the Expected has an error", []() {
        auto exp = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("error"));
        int defaultValue = 4;
        int value = exp.ValueOr(defaultValue);
        TEST_EQ(value, 4);
    });

    Describe("Expected:ValueOr(T &&)");

    It("returns the value when the Expected has a value", []() {
        auto exp = XexUtils::Expected<std::string, std::string>("some text");
        std::string defaultValue = "some default text";
        std::string value = exp.ValueOr(std::move(defaultValue));
        TEST_EQ(value, "some text");
    });

    It("returns the default value when the Expected has an error", []() {
        auto exp = XexUtils::Expected<std::string, std::string>(XexUtils::Unexpected<std::string>("error"));
        std::string defaultValue = "some default text";
        std::string value = exp.ValueOr(std::move(defaultValue));
        TEST_EQ(value, "some default text");
        TEST_EQ(defaultValue.size(), 0);
    });

    Describe("Expected::ErrorOr(const E &)");

    It("returns the error when the Expected has an error", []() {
        auto exp = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("error"));
        std::string defaultError = "default error";
        std::string error = exp.ErrorOr(defaultError);
        TEST_EQ(error, "error");
    });

    It("returns the default error when the Expected has a value", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        std::string defaultError = "default error";
        std::string error = exp.ErrorOr(defaultError);
        TEST_EQ(error, "default error");
    });

    Describe("Expected::ErrorOr(E &&)");

    It("returns the error when the Expected has an error", []() {
        auto exp = XexUtils::Expected<int, std::string>(XexUtils::Unexpected<std::string>("error"));
        std::string defaultError = "default error";
        std::string error = exp.ErrorOr(std::move(defaultError));
        TEST_EQ(error, "error");
    });

    It("returns the default error when the Expected has a value", []() {
        auto exp = XexUtils::Expected<int, std::string>(3);
        std::string defaultError = "default error";
        std::string error = exp.ErrorOr(std::move(defaultError));
        TEST_EQ(error, "default error");
        TEST_EQ(defaultError.size(), 0);
    });
}
