# Json

Parse primitive types:

```C++
void Init()
{
    std::string jsonString =
        "{"
        "  \"string\": \"foo\","
        "  \"number\": 3.2e3,"
        "  \"bool\": true,"
        "  \"null\": null"
        "}";

    XexUtils::Json::Node root = XexUtils::Json::Parse(jsonString);
    XexUtils::Json::Node string = root["string"];
    XexUtils::Json::Node number = root["number"];
    XexUtils::Json::Node boolean = root["bool"];
    XexUtils::Json::Node null = root["null"];

    root.GetType();    // XexUtils::Json::Node::Type_Object
    string.GetType();  // XexUtils::Json::Node::Type_String
    number.GetType();  // XexUtils::Json::Node::Type_Number
    boolean.GetType(); // XexUtils::Json::Node::Type_Bool
    null.GetType();    // XexUtils::Json::Node::Type_Null
    string.AsString(); // "foo"
    number.AsDouble(); // 3200.0
    boolean.AsBool();  // true
}
```

Parse complex types:

```C++
void Init()
{
    std::string jsonString =
        "{"
        "  \"object\": {"
        "    \"foo\": \"bar\""
        "  },"
        "  \"array\": [\"foo\", 3]"
        "}";

    XexUtils::Json::Node root = XexUtils::Json::Parse(jsonString);
    XexUtils::Json::Node object = root["object"];
    XexUtils::Json::Node objectFoo = object["foo"];
    XexUtils::Json::Node array = root["array"];
    XexUtils::Json::Node arrayFirst = array[0];
    XexUtils::Json::Node arraySecond = array[1];

    root.GetType();         // XexUtils::Json::Node::Type_Object
    object.GetType();       // XexUtils::Json::Node::Type_Object
    objectFoo.GetType();    // XexUtils::Json::Node::Type_String
    array.GetType();        // XexUtils::Json::Node::Type_Array
    arrayFirst.GetType();   // XexUtils::Json::Node::Type_String
    arraySecond.GetType();  // XexUtils::Json::Node::Type_Number
    objectFoo.AsString();   // "bar"
    arrayFirst.AsString();  // "foo"
    arraySecond.AsDouble(); // 3.0
}
```

Build primitive types:

```C++
void Init()
{
    XexUtils::Json::Node object =
        XexUtils::Json::Node()
            .AddChild("string", "foo")
            .AddChild("number", 3200.0)
            .AddChild("bool", true)
            .AddChild("null", nullptr);

    std::string jsonString = XexUtils::Json::Stringify(object);

    jsonString; // "{\"string\":\"foo\",\"null\":null,\"number\":3200,\"bool\":true}"
}
```

Build complex types:

```C++
void Init()
{
    XexUtils::Json::Node object =
        XexUtils::Json::Node()
            .AddChild("object", XexUtils::Json::Node().AddChild("foo", "bar"))
            .AddChild("array", XexUtils::Json::Node().AddElement("foo").AddElement(3.0));

    std::string jsonString = XexUtils::Json::Stringify(object);

    jsonString. // "{\"object\":{\"foo\":\"bar\"},\"array\":[\"foo\",3]}"
}
```

Check the presence of a key before accessing:

```C++
void Init()
{
    XexUtils::Json::Node object = Json::Parse("{\"foo\":\"bar\"}");

    if (object.Has("foo"))
        XexUtils::Log::Print("object has a 'foo' key.");
    else
        XexUtils::Log::Print("object doesn't have a 'foo' key.");
}
```

Check the size of the array elements before accessing:

```C++
void Init()
{
    XexUtils::Json::Node array = Json::Parse("[1, 2, 3]");

    if (array.Size() >= 2)
        XexUtils::Log::Print("I can safely access the second element: %f.", array[1].AsDouble());
    else
        XexUtils::Log::Print("I can't safely access the second element.");
}
```

> [!NOTE]
> Accessing an invalid key or index throws an exception. The `operator[]` methods call the `at` methods of `std::unordered_map` and `std::vector` internally.

Loop over the entries of an object:

```C++
void Init()
{
    XexUtils::Json::Node object = Json::Parse("{\"foo\":\"bar\",\"hello\":\"world\"}");
    const std::unordered_map<std::string, XexUtils::Json::Node> &children = object.GetChildren();

    for (auto it = children.begin(); it != children.end(); ++it)
        XexUtils::Log::Print("key: %s, value: %s", it->first.c_str(), it->second.AsString().c_str());
}
```

Loop over the elements of an array:

```C++
void Init()
{
    XexUtils::Json::Node array = Json::Parse("[1, 2, 3]");
    const std::vector<XexUtils::Json::Node> &elements = array.GetArrayElements();

    for (size_t i = 0; i < elements.size(); i++)
        XexUtils::Log::Print("index: %i, value: %f", i, elements[i].AsDouble());
}
```
