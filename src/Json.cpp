#include "pch.h"
#include "Json.h"

#include "Optional.h"

namespace XexUtils
{
namespace Json
{

Node::Node()
    : m_pParent(nullptr), m_Type(Type_Undefined)
{
}

Node::Node(const std::string &value)
    : m_pParent(nullptr), m_Type(Type_String), m_Data(value)
{
}

Node::Node(const char *value)
    : m_pParent(nullptr), m_Type(Type_String), m_Data(value)
{
}

Node::Node(bool value)
    : m_pParent(nullptr), m_Type(Type_Bool), m_Data(value ? "true" : "false")
{
}

Node::Node(double value)
    : m_pParent(nullptr), m_Type(Type_Number), m_Data(std::to_string(static_cast<long double>(value)))
{
}

Node::Node(nullptr_t)
    : m_pParent(nullptr), m_Type(Type_Null)
{
}

Node &Node::operator[](const std::string &key)
{
    return m_Children.at(key);
}

const Node &Node::operator[](const std::string &key) const
{
    return m_Children.at(key);
}

Node &Node::operator[](size_t index)
{
    return m_ArrayElements.at(index);
}

const Node &Node::operator[](size_t index) const
{
    return m_ArrayElements.at(index);
}

const std::string &Node::AsString() const
{
    return m_Data;
}

bool Node::AsBool() const
{
    return m_Type == Type_Bool && m_Data == "true";
}

double Node::AsDouble() const
{
    if (m_Type != Type_Number)
        return 0.0;

    return atof(m_Data.c_str());
}

Node &Node::operator=(const std::string &value)
{
    m_Type = Type_String;
    m_Data = value;
    return *this;
}

Node &Node::operator=(const char *value)
{
    m_Type = Type_String;
    m_Data = value;
    return *this;
}

Node &Node::operator=(bool value)
{
    m_Type = Type_Bool;
    m_Data = value ? "true" : "false";
    return *this;
}

Node &Node::operator=(double value)
{
    m_Type = Type_Number;
    m_Data = std::to_string(static_cast<long double>(value));
    return *this;
}

Node &Node::AddChild(const std::string &key, const Node &child)
{
    m_Type = Type_Object;
    m_Data.clear();

    m_Children[key] = child;
    m_Children[key].m_pParent = this;

    return *this;
}

Node &Node::AddElement(const Node &element)
{
    m_Type = Type_Array;
    m_Data.clear();

    m_ArrayElements.emplace_back(element);
    m_ArrayElements.back().m_pParent = this;

    return *this;
}

Node::Type Node::GetType() const
{
    return m_Type;
}

bool Node::Has(const std::string &key) const
{
    return m_Type == Type_Object && m_Children.find(key) != m_Children.end();
}

size_t Node::Size() const
{
    return m_Type == Type_Array ? m_ArrayElements.size() : 0;
}

std::unordered_map<std::string, Node> &Node::GetChildren()
{
    return m_Children;
}

const std::unordered_map<std::string, Node> &Node::GetChildren() const
{
    return m_Children;
}

std::vector<Node> &Node::GetArrayElements()
{
    return m_ArrayElements;
}

const std::vector<Node> &Node::GetArrayElements() const
{
    return m_ArrayElements;
}

Node Parse(const std::string &data)
{
    // Create the reader
    HJSONREADER reader = XJSONCreateReader();
    Node root;

    // Feed the string to the reader
    HRESULT hr = XJSONSetBuffer(reader, data.c_str(), data.size(), TRUE);
    if (FAILED(hr))
    {
        DebugPrint("[XexUtils][Json]: Error: Couldn't set the JSON buffer: %X.", hr);
        return root;
    }

    Node *pCurrentNode = &root;
    DWORD tokenLength = 0;
    DWORD parsed = 0;
    JSONTOKENTYPE tokenType = Json_NotStarted;
    Optional<std::string> pendingKey;

    auto EnterContainer = [&](Node::Type type) {
        XASSERT(type == Node::Type_Array || type == Node::Type_Object);

        // Create the new container
        Node container;
        container.m_Type = type;

        if (pCurrentNode->m_Type == Node::Type_Array)
        {
            // Append the new container to the array elements of the current node
            &pCurrentNode->AddElement(container);

            // The current node is now the new container we just inserted
            pCurrentNode = &pCurrentNode->GetArrayElements().back();
        }
        else if (pendingKey)
        {
            // If we just encountered a field name, the current node is an object and we
            // add the new container to its map of children
            pCurrentNode->AddChild(*pendingKey, container);

            // The current node is now the new container we just inserted
            pCurrentNode = &pCurrentNode->GetChildren().at(*pendingKey);

            pendingKey = NullOpt();
        }
        else
        {
            // If the current node has a primitive type (not object nor array), it becomes
            // the new container
            *pCurrentNode = container;
        }
    };

    auto ExitContainer = [&]() {
        // Go up one level in the tree hierarchy
        if (pCurrentNode != nullptr && pCurrentNode->m_pParent != nullptr)
            pCurrentNode = pCurrentNode->m_pParent;
    };

    auto ReadNextToken = [&]() -> std::string {
        std::unique_ptr<char[]> value(new char[tokenLength + 1]());
        XJSONGetTokenValue(reader, value.get(), tokenLength + 1);

        return value.get();
    };

    auto SetValue = [&](Node::Type type) {
        std::string token = ReadNextToken();
        Node newNode;
        newNode.m_Data = token;
        newNode.m_Type = type;

        if (pCurrentNode->m_Type == Node::Type_Array)
        {
            // Append the new node to the array elements of the current node
            pCurrentNode->AddElement(newNode);
        }
        else if (pendingKey)
        {
            // If we just encountered a field name, the current node is an object and we
            // add the new node to its map of children
            pCurrentNode->AddChild(*pendingKey, newNode);
            pendingKey = NullOpt();
        }
        else
        {
            // If the current node has a primitive type (not object nor array), we update
            // it with the new data and type
            pCurrentNode->m_Data = token;
            pCurrentNode->m_Type = type;
        }
    };

    while (XJSONReadToken(reader, &tokenType, &tokenLength, &parsed) == S_OK)
    {
        switch (tokenType)
        {
        case Json_BeginObject:
        case Json_BeginArray:
            EnterContainer(Node::TokenTypeToNodeType(tokenType));
            break;
        case Json_EndObject:
        case Json_EndArray:
            ExitContainer();
            break;
        case Json_FieldName:
            pendingKey = ReadNextToken();
            break;
        case Json_String:
        case Json_Number:
        case Json_True:
        case Json_False:
        case Json_Null:
            SetValue(Node::TokenTypeToNodeType(tokenType));
            break;
        }
    }

    XJSONCloseReader(reader);

    return *pCurrentNode;
}

static HRESULT WriteJson(HJSONWRITER writer, const Node &node)
{
    HRESULT hr = S_OK;

    switch (node.GetType())
    {
    case Node::Type_Array: {
        // Start the array
        hr = XJSONBeginArray(writer);
        if (FAILED(hr))
        {
            DebugPrint("[XexUtils][Json]: Error: Couldn't begin an array: %X.", hr);
            return hr;
        }

        // Recursively convert to JSON all the array elements
        const auto &elements = node.GetArrayElements();
        for (size_t i = 0; i < elements.size(); i++)
        {
            hr = WriteJson(writer, elements[i]);
            if (FAILED(hr))
                return hr;
        }

        // End the the array
        hr = XJSONEndArray(writer);
        if (FAILED(hr))
        {
            DebugPrint("[XexUtils][Json]: Error: Couldn't end an array: %X.", hr);
            return hr;
        }

        break;
    }
    case Node::Type_Object: {
        // Start the object
        hr = XJSONBeginObject(writer);
        if (FAILED(hr))
        {
            DebugPrint("[XexUtils][Json]: Error: Couldn't begin an object: %X.", hr);
            return hr;
        }

        // Recursively convert to JSON all the children
        const auto &children = node.GetChildren();
        for (auto it = children.begin(); it != children.end(); ++it)
        {
            // Start the field with the name
            hr = XJSONBeginField(writer, it->first.c_str(), it->first.size());
            if (FAILED(hr))
            {
                DebugPrint("[XexUtils][Json]: Error: Couldn't begin a field: %X.", hr);
                return hr;
            }

            // Write the value
            hr = WriteJson(writer, it->second);
            if (FAILED(hr))
                return hr;

            // End the field with the separator
            hr = XJSONEndField(writer);
            if (FAILED(hr))
            {
                DebugPrint("[XexUtils][Json]: Error: Couldn't end a field: %X.", hr);
                return hr;
            }
        }

        // End the object
        hr = XJSONEndObject(writer);
        if (FAILED(hr))
        {
            DebugPrint("[XexUtils][Json]: Error: Couldn't end an object: %X.", hr);
            return hr;
        }

        break;
    }
    case Node::Type_Null: {
        // Write a null value
        hr = XJSONWriteNullValue(writer);
        if (FAILED(hr))
        {
            DebugPrint("[XexUtils][Json]: Error: Couldn't write a null value: %X.", hr);
            return hr;
        }

        break;
    }
    case Node::Type_String: {
        // Write a string value
        hr = XJSONWriteStringValue(writer, node.AsString().c_str(), node.AsString().size());
        if (FAILED(hr))
        {
            DebugPrint("[XexUtils][Json]: Error: Couldn't write a string value: %X.", hr);
            return hr;
        }

        break;
    }
    case Node::Type_Number: {
        // Write a number value
        hr = XJSONWriteNumberValue(writer, node.AsDouble());
        if (FAILED(hr))
        {
            DebugPrint("[XexUtils][Json]: Error: Couldn't write a number value: %X.", hr);
            return hr;
        }

        break;
    }
    case Node::Type_Bool: {
        // Write a bool value
        hr = XJSONWriteBooleanValue(writer, node.AsBool());
        if (FAILED(hr))
        {
            DebugPrint("[XexUtils][Json]: Error: Couldn't write a bool value: %X.", hr);
            return hr;
        }

        break;
    }
    }

    return S_OK;
}

std::string Stringify(const Node &node)
{
    // Create the writer
    HJSONWRITER writer = XJSONCreateWriter();

    // Recursively write the tree
    HRESULT hr = WriteJson(writer, node);
    if (FAILED(hr))
    {
        XJSONCloseWriter(writer);
        return "";
    }

    // Call XJSONGetBuffer a first time with a null buffer and an empty size to query
    // how big of a buffer is needed to store the final string.
    // This is the same pattern as MultiByteToWideChar or WideCharToMultiByte
    DWORD requiredBufferSize = 0;
    hr = XJSONGetBuffer(writer, static_cast<char *>(nullptr), &requiredBufferSize);
    if (hr != JSON_E_BUFFER_TOO_SMALL)
    {
        DebugPrint(
            "[XexUtils][Json]: Error: Couldn't get the required size for the buffer string: %X.",
            hr
        );
        XJSONCloseWriter(writer);
        return "";
    }

    // Write the JSON string into the previously created buffer
    std::unique_ptr<char[]> buffer(new char[requiredBufferSize]());
    hr = XJSONGetBuffer(writer, buffer.get(), &requiredBufferSize);
    if (FAILED(hr))
    {
        DebugPrint("[XexUtils][Json]: Error: Couldn't get the buffer string: %X.", hr);
        XJSONCloseWriter(writer);
        return "";
    }

    XJSONCloseWriter(writer);

    return buffer.get();
}

Node::Type Node::TokenTypeToNodeType(JSONTOKENTYPE tokenType)
{
    switch (tokenType)
    {
    case Json_BeginObject:
    case Json_EndObject:
        return Type_Object;
    case Json_BeginArray: {
    case Json_EndArray:
        return Type_Array;
    case Json_String:
        return Type_String;
    case Json_Number:
        return Type_Number;
    case Json_True:
    case Json_False:
        return Type_Bool;
    case Json_Null:
        return Type_Null;
    default:
        return Type_Undefined;
    }
    }
}

}
}
