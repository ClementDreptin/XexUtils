#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Json()
{
    Describe("Json::Node::Node()");

    It("constructs an empty Node", []() {
        Json::Node node;

        TEST_EQ(node.GetType(), Json::Node::Type_Undefined);
    });

    Describe("Json::Node::Node(const std::string &)");

    It("constructs a Node from an std::string", []() {
        std::string string("hello");
        Json::Node node(string);

        TEST_EQ(node.GetType(), Json::Node::Type_String);
        TEST_EQ(node.AsString(), "hello");
    });

    Describe("Json::Node::Node(std::string &&)");

    It("constructs a Node from a moved std::string", []() {
        std::string string("hello");
        Json::Node node(std::move(string));

        TEST_EQ(node.GetType(), Json::Node::Type_String);
        TEST_EQ(node.AsString(), "hello");
        TEST_EQ(string.size(), 0);
    });

    Describe("Json::Node::Node(const char *)");

    It("constructs a Node from a const char *", []() {
        Json::Node node("hello");

        TEST_EQ(node.GetType(), Json::Node::Type_String);
        TEST_EQ(node.AsString(), "hello");
    });

    Describe("Json::Node::Node(bool)");

    It("constructs a Node from a bool", []() {
        Json::Node node(true);

        TEST_EQ(node.GetType(), Json::Node::Type_Bool);
        TEST_EQ(node.AsBool(), true);
        TEST_EQ(node.AsString(), "true");
    });

    Describe("Json::Node::Node(double)");

    It("constructs a Node from a double", []() {
        Json::Node node(3.0);

        TEST_EQ(node.GetType(), Json::Node::Type_Number);
        TEST_EQ(node.AsDouble(), 3.0);
        TEST_EQ(node.AsString(), "3");
    });

    Describe("Json::Node::Node(nullptr_t)");

    It("constructs a Node from a nullptr", []() {
        Json::Node node(nullptr);

        TEST_EQ(node.GetType(), Json::Node::Type_Null);
        TEST_EQ(node.AsString(), "");
    });

    Describe("Json::Node::operator[](const std::string &)");

    It("returns the child Node at the key", []() {
        auto obj = Json::Parse("{\"foo\":3}");
        auto foo = obj["foo"];

        TEST_EQ(foo.GetType(), Json::Node::Type_Number);
        TEST_EQ(foo.AsDouble(), 3);
    });

    It("throws an exception when the Node doesn't have a child Node at the key", []() {
        auto obj = Json::Parse("{\"foo\":3}");
        bool dummy = true;

        try
        {
            obj["bar"];
            TEST_EQ(dummy, false);
        }
        catch (...)
        {
            TEST_EQ(dummy, true);
        }
    });

    Describe("Json::Node::operator[](size_t)");

    It("returns the array element at the index", []() {
        auto array = Json::Parse("[1,2,3]");
        auto second = array[1];

        TEST_EQ(second.GetType(), Json::Node::Type_Number);
        TEST_EQ(second.AsDouble(), 2);
    });

    It("throws an exception when the Node doesn't have an array element at the index", []() {
        auto array = Json::Parse("[1,2,3]");
        bool dummy = true;

        try
        {
            array[6];
            TEST_EQ(dummy, false);
        }
        catch (...)
        {
            TEST_EQ(dummy, true);
        }
    });

    Describe("Json::Node::AsString()");

    It("returns the raw internal Node data", []() {
        auto obj = Json::Parse("{\"foo\":3,\"bar\":\"baz\"}");
        auto foo = obj["foo"];
        auto bar = obj["bar"];

        TEST_EQ(foo.GetType(), Json::Node::Type_Number);
        TEST_EQ(foo.AsString(), "3");
        TEST_EQ(bar.GetType(), Json::Node::Type_String);
        TEST_EQ(bar.AsString(), "baz");
    });

    Describe("Json::Node::AsBool()");

    It("returns true if the internal data is \"true\" and the Node type is bool", []() {
        auto obj = Json::Parse("{\"foo\":true}");
        auto foo = obj["foo"];

        TEST_EQ(foo.GetType(), Json::Node::Type_Bool);
        TEST_EQ(foo.AsBool(), true);
    });

    It("returns false if the internal data is \"true\" but the Node type is not bool", []() {
        auto obj = Json::Parse("{\"foo\":\"true\"}");
        auto foo = obj["foo"];

        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(foo.AsBool(), false);
    });

    It("returns false if the internal data is \"false\" and the Node type is bool", []() {
        auto obj = Json::Parse("{\"foo\":false}");
        auto foo = obj["foo"];

        TEST_EQ(foo.GetType(), Json::Node::Type_Bool);
        TEST_EQ(foo.AsBool(), false);
    });

    It("returns false if the Node type is not a bool", []() {
        auto obj = Json::Parse("{\"foo\":\"bar\"}");
        auto foo = obj["foo"];

        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(foo.AsBool(), false);
    });

    Describe("Json::Node::AsDouble()");

    It("returns a the double if the Node type is number", []() {
        auto obj = Json::Parse("{\"foo\":3}");
        auto foo = obj["foo"];

        TEST_EQ(foo.GetType(), Json::Node::Type_Number);
        TEST_EQ(foo.AsDouble(), 3);
    });

    It("returns 0 if the internal data is \"0\" and the Node type is number", []() {
        auto obj = Json::Parse("{\"foo\":0}");
        auto foo = obj["foo"];

        TEST_EQ(foo.GetType(), Json::Node::Type_Number);
        TEST_EQ(foo.AsDouble(), 0);
    });

    It("returns 0 if the Node type is not number", []() {
        auto obj = Json::Parse("{\"foo\":\"bar\"}");
        auto foo = obj["foo"];

        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(foo.AsDouble(), 0);
    });

    Describe("Json::Node::operator=(const std::string &)");

    It("sets the internal data to the std::string", []() {
        auto obj = Json::Parse("{\"foo\":3}");
        auto foo = obj["foo"];
        foo = "bar";

        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(foo.AsString(), "bar");
    });

    Describe("Json::Node::operator=(bool)");

    It("converts the bool to a string and sets the internal data to the result", []() {
        auto obj = Json::Parse("{\"foo\":3}");
        auto foo = obj["foo"];
        foo = true;

        TEST_EQ(foo.GetType(), Json::Node::Type_Bool);
        TEST_EQ(foo.AsBool(), true);
        TEST_EQ(foo.AsString(), "true");
    });

    Describe("Json::Node::operator=(double)");

    It("converts the double to a string and sets the internal data to the result", []() {
        auto obj = Json::Parse("{\"foo\":true}");
        auto foo = obj["foo"];
        foo = 3.0;

        TEST_EQ(foo.GetType(), Json::Node::Type_Number);
        TEST_EQ(foo.AsDouble(), 3.0);
        TEST_EQ(foo.AsString(), "3");
    });

    Describe("Json::Node::AddChild(const std::string &, const Json::Node &)");

    It("adds a child to the Node", []() {
        auto obj = Json::Node().AddChild("foo", "bar");
        auto foo = obj["foo"];
        std::string value = foo.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "bar");
    });

    It("sets the type of the Node to Type_Object and clears the internal data", []() {
        Json::Node node("hello");
        TEST_EQ(node.GetType(), Json::Node::Type_String);
        TEST_EQ(node.AsString(), "hello");

        node.AddChild("foo", "bar");
        TEST_EQ(node.GetType(), Json::Node::Type_Object);
        TEST_EQ(node.AsString(), "");
    });

    It("supports building nested objects", []() {
        auto obj =
            Json::Node()
                .AddChild("foo", "bar")
                .AddChild("fizz", Json::Node().AddChild("buzz", "baz"));

        auto foo = obj["foo"];
        auto fizz = obj["fizz"];
        auto fizzBuzz = fizz["buzz"];
        std::string fooValue = foo.AsString();
        std::string fizzBuzzValue = fizzBuzz.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(fizz.GetType(), Json::Node::Type_Object);
        TEST_EQ(fizzBuzz.GetType(), Json::Node::Type_String);
        TEST_EQ(fooValue, "bar");
        TEST_EQ(fizzBuzzValue, "baz");
    });

    Describe("Json::Node::AddElement(const Json::Node &)");

    It("adds an element to the Node", []() {
        auto array = Json::Node().AddElement("foo");
        auto first = array[0];
        std::string firstValue = first.AsString();

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_String);
        TEST_EQ(firstValue, "foo");
    });

    It("sets the type of the Node to Type_Array and clears the internal data", []() {
        Json::Node node("hello");
        TEST_EQ(node.GetType(), Json::Node::Type_String);
        TEST_EQ(node.AsString(), "hello");

        node.AddElement("foo");
        TEST_EQ(node.GetType(), Json::Node::Type_Array);
        TEST_EQ(node.AsString(), "");
    });

    It("supports building nested arrays", []() {
        auto array =
            Json::Node()
                .AddElement("foo")
                .AddElement(Json::Node().AddElement("bar"));

        auto first = array[0];
        auto second = array[1];
        auto secondFirst = second[0];
        std::string firstValue = first.AsString();
        std::string secondFirstValue = secondFirst.AsString();

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_String);
        TEST_EQ(second.GetType(), Json::Node::Type_Array);
        TEST_EQ(secondFirst.GetType(), Json::Node::Type_String);
        TEST_EQ(firstValue, "foo");
        TEST_EQ(secondFirstValue, "bar");
    });

    Describe("Json::Node::GetType()");

    It("returns the Node type", []() {
        auto array = Json::Parse("[{},[],true,false,\"foo\",3.2,null]");
        auto first = array[0];
        auto second = array[1];
        auto third = array[2];
        auto fourth = array[3];
        auto fifth = array[4];
        auto sixth = array[5];
        auto seventh = array[6];

        TEST_EQ(first.GetType(), Json::Node::Type_Object);
        TEST_EQ(second.GetType(), Json::Node::Type_Array);
        TEST_EQ(third.GetType(), Json::Node::Type_Bool);
        TEST_EQ(fourth.GetType(), Json::Node::Type_Bool);
        TEST_EQ(fifth.GetType(), Json::Node::Type_String);
        TEST_EQ(sixth.GetType(), Json::Node::Type_Number);
        TEST_EQ(seventh.GetType(), Json::Node::Type_Null);
    });

    Describe("Json::Node::Has(const std::string &)");

    It("returns true when the Node is of type object and has a child at the given key", []() {
        auto obj = Json::Node().AddChild("foo", "bar");

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(obj.Has("foo"), true);
    });

    It("returns false when the Node is of type object but doesn't have a child at the given key", []() {
        auto obj = Json::Node().AddChild("foo", "bar");

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(obj.Has("other"), false);
    });

    It("returns false when the Node is not of type object", []() {
        auto obj = Json::Node().AddElement("foo");

        TEST_EQ(obj.GetType(), Json::Node::Type_Array);
        TEST_EQ(obj.Has("foo"), false);
    });

    Describe("Json::Node::Size()");

    It("returns the size of the array elements when the Node is of type array", []() {
        auto array = Json::Node().AddElement("foo").AddElement("bar");

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(array.Size(), 2);
    });

    It("returns 0 when the Node is not of type array", []() {
        auto obj = Json::Node().AddChild("foo", "bar");

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(obj.Size(), 0);
    });

    Describe("Json::Node::GetChildren()");

    It("returns the children as an std::unordered_map<std::string, Node>", []() {
        auto obj = Json::Parse("{\"foo\":3}");
        const auto &children = obj.GetChildren();

        TEST_EQ(children.size(), 1);
        TEST_EQ(children.at("foo").AsString(), "3");
    });

    It("returns an empty std::unordered_map<std::string, Node> when the Node is not of type object", []() {
        auto array = Json::Parse("[1,2,3]");
        const auto &children = array.GetChildren();

        TEST_EQ(children.size(), 0);
    });

    Describe("Json::Node::GetArrayElements()");

    It("returns the array elements as an std::vector<Node>", []() {
        auto array = Json::Parse("[1,2,3]");
        const auto &arrayElements = array.GetArrayElements();

        TEST_EQ(arrayElements.size(), 3);
        TEST_EQ(arrayElements[0].AsString(), "1");
        TEST_EQ(arrayElements[1].AsString(), "2");
        TEST_EQ(arrayElements[2].AsString(), "3");
    });

    It("returns an empty std::vector<Node> when the Node is not of type array", []() {
        auto obj = Json::Parse("{\"foo\":3}");
        const auto &arrayElements = obj.GetArrayElements();

        TEST_EQ(arrayElements.size(), 0);
    });

    Describe("Json::Parse(const std::string &)");

    It("parses an empty object", []() {
        auto obj = Json::Parse("{}");

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(obj.Has("foo"), false);
    });

    It("parses an object with a string value", []() {
        auto obj = Json::Parse("{\"foo\":\"bar\"}");
        auto foo = obj["foo"];
        std::string value = foo.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "bar");
    });

    It("parses an object with an empty string value", []() {
        auto obj = Json::Parse("{\"foo\":\"\"}");
        auto foo = obj["foo"];
        std::string value = foo.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "");
    });

    It("parses an object with a number value", []() {
        auto obj = Json::Parse("{\"foo\":3}");
        auto foo = obj["foo"];
        double value = foo.AsDouble();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_Number);
        TEST_EQ(value, 3.0);
    });

    It("parses an object with a number value in scientific notation (positive power)", []() {
        auto obj = Json::Parse("{\"foo\":3e3}");
        auto foo = obj["foo"];
        double value = foo.AsDouble();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_Number);
        TEST_EQ(value, 3000.0);
    });

    It("parses an object with a number value in scientific notation (negative power)", []() {
        auto obj = Json::Parse("{\"foo\":3e-3}");
        auto foo = obj["foo"];
        double value = foo.AsDouble();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_Number);
        TEST_EQ(value, 0.003);
    });

    It("parses an object with a boolean value", []() {
        auto obj = Json::Parse("{\"foo\":true,\"bar\":false}");
        auto foo = obj["foo"];
        auto bar = obj["bar"];
        bool fooValue = foo.AsBool();
        bool barValue = bar.AsBool();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_Bool);
        TEST_EQ(bar.GetType(), Json::Node::Type_Bool);
        TEST_EQ(fooValue, true);
        TEST_EQ(barValue, false);
    });

    It("parses an object with a null value", []() {
        auto obj = Json::Parse("{\"foo\":null}");
        auto foo = obj["foo"];

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_Null);
    });

    It("parses a nested object", []() {
        auto obj = Json::Parse("{\"foo\":{\"bar\":\"baz\"}}");
        auto foo = obj["foo"];
        auto fooBar = foo["bar"];
        std::string value = fooBar.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_Object);
        TEST_EQ(fooBar.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "baz");
    });

    It("parses an object with multiple pairs", []() {
        auto obj = Json::Parse("{\"foo\":\"bar\",\"hello\":\"world\"}");
        auto foo = obj["foo"];
        auto hello = obj["hello"];
        std::string fooValue = foo.AsString();
        std::string helloValue = hello.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(hello.GetType(), Json::Node::Type_String);
        TEST_EQ(fooValue, "bar");
        TEST_EQ(helloValue, "world");
    });

    It("parses a nested object with multiple pairs", []() {
        auto obj = Json::Parse("{\"nested\":{\"first\":\"firstValue\",\"second\":\"secondValue\"},\"after\":\"afterValue\"}");
        auto nested = obj["nested"];
        auto first = nested["first"];
        auto second = nested["second"];
        auto after = obj["after"];
        std::string firstValue = first.AsString();
        std::string secondValue = second.AsString();
        std::string afterValue = after.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(nested.GetType(), Json::Node::Type_Object);
        TEST_EQ(first.GetType(), Json::Node::Type_String);
        TEST_EQ(second.GetType(), Json::Node::Type_String);
        TEST_EQ(after.GetType(), Json::Node::Type_String);
        TEST_EQ(firstValue, "firstValue");
        TEST_EQ(secondValue, "secondValue");
        TEST_EQ(afterValue, "afterValue");
    });

    It("parses a pair after a nested object", []() {
        auto obj = Json::Parse("{\"foo\":{\"bar\":\"baz\"},\"hello\":\"world\"}");
        auto hello = obj["hello"];
        std::string value = hello.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(hello.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "world");
    });

    It("parses an object with an escaped key", []() {
        auto obj = Json::Parse("{\"key\\nwith\\nnewlines\":\"hello\"}");
        auto keyWithNewLines = obj["key\nwith\nnewlines"];
        std::string value = keyWithNewLines.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(keyWithNewLines.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "hello");
    });

    It("parses an object with an empty key", []() {
        auto obj = Json::Parse("{\"\":\"hello\"}");
        auto empty = obj[""];
        std::string value = empty.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(empty.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "hello");
    });

    It("parses an empty array", []() {
        auto array = Json::Parse("[]");
        size_t size = array.GetArrayElements().size();

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(size, 0);
    });

    It("parses an array of strings", []() {
        auto array = Json::Parse("[\"foo\",\"bar\"]");
        auto first = array[0];
        auto second = array[1];
        std::string firstValue = first.AsString();
        std::string secondValue = second.AsString();

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_String);
        TEST_EQ(second.GetType(), Json::Node::Type_String);
        TEST_EQ(firstValue, "foo");
        TEST_EQ(secondValue, "bar");
    });

    It("parses an array of numbers", []() {
        auto array = Json::Parse("[3,3.2,3.1e3,3.1e-3]");
        auto first = array[0];
        auto second = array[1];
        auto third = array[2];
        auto fourth = array[3];
        double firstValue = first.AsDouble();
        double secondValue = second.AsDouble();
        double thirdValue = third.AsDouble();
        double fourthValue = fourth.AsDouble();

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_Number);
        TEST_EQ(second.GetType(), Json::Node::Type_Number);
        TEST_EQ(third.GetType(), Json::Node::Type_Number);
        TEST_EQ(fourth.GetType(), Json::Node::Type_Number);
        TEST_EQ(firstValue, 3.0);
        TEST_EQ(secondValue, 3.2);
        TEST_EQ(thirdValue, 3100.0);
        TEST_EQ(fourthValue, 0.0031);
    });

    It("parses an array of booleans", []() {
        auto array = Json::Parse("[true,false]");
        auto first = array[0];
        auto second = array[1];
        bool firstValue = first.AsBool();
        bool secondValue = second.AsBool();

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_Bool);
        TEST_EQ(second.GetType(), Json::Node::Type_Bool);
        TEST_EQ(firstValue, true);
        TEST_EQ(secondValue, false);
    });

    It("parses an array of nulls", []() {
        auto array = Json::Parse("[null,null]");
        auto first = array[0];
        auto second = array[1];

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_Null);
        TEST_EQ(second.GetType(), Json::Node::Type_Null);
    });

    It("parses an array of objects", []() {
        auto array = Json::Parse("[{\"foo\":\"bar\"},{\"hello\":\"world\"}]");
        auto first = array[0];
        auto second = array[1];
        auto foo = first["foo"];
        auto hello = second["hello"];
        std::string fooValue = foo.AsString();
        std::string helloValue = hello.AsString();

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_Object);
        TEST_EQ(second.GetType(), Json::Node::Type_Object);
        TEST_EQ(foo.GetType(), Json::Node::Type_String);
        TEST_EQ(hello.GetType(), Json::Node::Type_String);
        TEST_EQ(fooValue, "bar");
        TEST_EQ(helloValue, "world");
    });

    It("parses an array of different types", []() {
        auto array = Json::Parse("[{},[],true,false,\"foo\",3.2]");
        auto first = array[0];
        auto second = array[1];
        auto third = array[2];
        auto fourth = array[3];
        auto fifth = array[4];
        auto sixth = array[5];

        TEST_EQ(first.GetType(), Json::Node::Type_Object);
        TEST_EQ(second.GetType(), Json::Node::Type_Array);
        TEST_EQ(third.GetType(), Json::Node::Type_Bool);
        TEST_EQ(fourth.GetType(), Json::Node::Type_Bool);
        TEST_EQ(fifth.GetType(), Json::Node::Type_String);
        TEST_EQ(sixth.GetType(), Json::Node::Type_Number);
    });

    It("parses a nested array", []() {
        auto array = Json::Parse("[[\"foo\",\"bar\"],[\"hello\",\"world\"]]");
        auto first = array[0];
        auto second = array[1];
        auto firstFirst = first[0];
        auto secondSecond = second[1];
        std::string firstFirstValue = firstFirst.AsString();
        std::string secondSecondValue = secondSecond.AsString();

        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_Array);
        TEST_EQ(second.GetType(), Json::Node::Type_Array);
        TEST_EQ(firstFirst.GetType(), Json::Node::Type_String);
        TEST_EQ(secondSecond.GetType(), Json::Node::Type_String);
        TEST_EQ(firstFirstValue, "foo");
        TEST_EQ(secondSecondValue, "world");
    });

    It("parses an array nested in an object", []() {
        auto obj = Json::Parse("{\"foo\":[{\"hello\":\"world\"}]}");
        auto array = obj["foo"];
        auto first = array[0];
        auto firstHello = first["hello"];
        std::string value = firstHello.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(array.GetType(), Json::Node::Type_Array);
        TEST_EQ(first.GetType(), Json::Node::Type_Object);
        TEST_EQ(firstHello.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "world");
    });

    It("parses a pair after a nested array", []() {
        auto obj = Json::Parse("{\"foo\":[\"bar\",\"baz\"],\"hello\":\"world\"}");
        auto hello = obj["hello"];
        std::string value = hello.AsString();

        TEST_EQ(obj.GetType(), Json::Node::Type_Object);
        TEST_EQ(hello.GetType(), Json::Node::Type_String);
        TEST_EQ(value, "world");
    });

    Describe("Json::Stringify(const Json::Node &)");

    It("stringifies an empty object", []() {
        std::string inputString = "{}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an object with a string value", []() {
        std::string inputString = "{\"foo\":\"bar\"}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an object with an empty string value", []() {
        std::string inputString = "{\"foo\":\"\"}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an object with a number value", []() {
        std::string inputString = "{\"foo\":3}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an object with a number value in scientific notation (positive power)", []() {
        std::string inputString = "{\"foo\":3e3}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(outputString, "{\"foo\":3000}");
    });

    It("stringifies an object with a number value in scientific notation (negative power)", []() {
        std::string inputString = "{\"foo\":3e-3}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(outputString, "{\"foo\":0.003}");
    });

    It("stringifies an object with a boolean value", []() {
        std::string inputString = "{\"foo\":true,\"bar\":false}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an object with a null value", []() {
        std::string inputString = "{\"foo\":null}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies a nested object", []() {
        std::string inputString = "{\"foo\":{\"bar\":\"baz\"}}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an object with multiple pairs", []() {
        std::string inputString = "{\"foo\":\"bar\",\"hello\":\"world\"}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies a nested object with multiple pairs", []() {
        std::string inputString = "{\"nested\":{\"first\":\"firstValue\",\"second\":\"secondValue\"},\"after\":\"afterValue\"}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies a pair after a nested object", []() {
        std::string inputString = "{\"foo\":{\"bar\":\"baz\"},\"hello\":\"world\"}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an object with an escaped key", []() {
        std::string inputString = "{\"key\\nwith\\nnewlines\":\"hello\"}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an object with an empty key", []() {
        std::string inputString = "{\"\":\"hello\"}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an empty array", []() {
        std::string inputString = "[]";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an array of strings", []() {
        std::string inputString = "[\"foo\",\"bar\"]";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an array of numbers", []() {
        std::string inputString = "[3,3.2,3.1e3,3.1e-3]";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(outputString, "[3,3.2,3100,0.0031]");
    });

    It("stringifies an array of booleans", []() {
        std::string inputString = "[true,false]";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an array of nulls", []() {
        std::string inputString = "[null,null]";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an array of objects", []() {
        std::string inputString = "[{\"foo\":\"bar\"},{\"hello\":\"world\"}]";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an array of different types", []() {
        std::string inputString = "[{},[],true,false,\"foo\",3.2]";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies a nested array", []() {
        std::string inputString = "[[\"foo\",\"bar\"],[\"hello\",\"world\"]]";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies an array nested in an object", []() {
        std::string inputString = "{\"foo\":[{\"hello\":\"world\"}]}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });

    It("stringifies a pair after a nested array", []() {
        std::string inputString = "{\"foo\":[\"bar\",\"baz\"],\"hello\":\"world\"}";
        auto parsed = Json::Parse(inputString);
        std::string outputString = Json::Stringify(parsed);

        TEST_EQ(inputString, outputString);
    });
}
