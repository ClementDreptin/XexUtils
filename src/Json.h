#pragma once

namespace XexUtils
{
namespace Json
{

/// @brief A class to represent a node within a JSON tree.
class Node
{
public:
    /// @brief An enum to represent the different `Node` types.
    typedef enum _Type
    {
        Type_Undefined,
        Type_Null,
        Type_String,
        Type_Number,
        Type_Bool,
        Type_Array,
        Type_Object,
    } Type;

    /// @brief Creates an empty `Node` (type `Type_Undefined`).
    Node();

    /// @brief Creates a leaf `Node` of type `Type_String`.
    /// @param value The value.
    Node(const std::string &value);

    /// @brief Creates a leaf `Node` of type `Type_String`.
    /// @param value The value.
    Node(const char *value);

    /// @brief Creates a leaf `Node` of type `Type_Bool`.
    /// @param value The value.
    Node(bool value);

    /// @brief Creates a leaf `Node` of type `Type_Number`.
    /// @param value The value.
    Node(double value);

    /// @brief Creates a leaf `Node` of type `Type_Null`.
    Node(nullptr_t);

    /// @brief Gets the child `Node` at `key`.
    ///
    /// If the current `Node` doesn't have a child at `key`, an `std::out_of_range`
    /// exception is thrown. This behavior is inherited from `std::unordered_map::at`.
    ///
    /// @param key The key.
    /// @return A reference to the child `Node` at `key`.
    Node &operator[](const std::string &key);

    /// @brief Gets the child `Node` at `key` (const version).
    ///
    /// If the current `Node` doesn't have a child at `key`, an `std::out_of_range`
    /// exception is thrown. This behavior is inherited from `std::unordered_map::at`.
    ///
    /// @param key The key.
    /// @return A const reference to the child `Node` at `key`.
    const Node &operator[](const std::string &key) const;

    /// @brief Gets the child `Node` at `index`.
    ///
    /// If the current `Node` is not an array or if the `index` is out of bounds, an
    /// `std::out_of_range` exception is thrown. This behavior is inherited from
    /// `std::vector::at`.
    ///
    /// @param index The index.
    /// @return A reference to the child `Node` at `index`.
    Node &operator[](size_t index);

    /// @brief Gets the child `Node` at `index` (const version).
    ///
    /// If the current `Node` is not an array or if the `index` is out of bounds, an
    /// `std::out_of_range` exception is thrown. This behavior is inherited from
    /// `std::vector::at`.
    ///
    /// @param index The index.
    /// @return A const reference to the child `Node` at `index`.
    const Node &operator[](size_t index) const;

    /// @brief Gets the internal data.
    /// @return The internal data.
    const std::string &AsString() const;

    /// @brief Converts the internal data (`std::string`) into a `bool`.
    ///
    /// This function returns `true` if the current `Node` is of type `Type_Bool` and if
    /// the internal data is "true", `false` is returned otherwise.
    ///
    /// @return The internal data converted into a `bool`.
    bool AsBool() const;

    /// @brief Converts the internal data (`std::string`) into a `double`.
    ///
    /// If the current `Node` is not of type `Type_Number` or if the internal data could
    /// not be converted into a `double`, `0.0` is returned.
    ///
    /// @return The internal data converted into a `double`.
    double AsDouble() const;

    /// @brief Sets the internal data (`std::string`).
    /// @param value The value.
    /// @return A reference to the current `Node`.
    Node &operator=(const std::string &value);

    /// @brief Sets the internal data (`std::string`).
    /// @param value The value.
    /// @return A reference to the current `Node`.
    Node &operator=(const char *value);

    /// @brief Sets the internal data (`std::string`) to "true" or "false", depending on
    /// `value`.
    /// @param value The value.
    /// @return A reference to the current `Node`.
    Node &operator=(bool value);

    /// @brief Sets the internal data (`std::string`) to `value` converted into a string.
    /// @param value The value.
    /// @return A reference to the current `Node`.
    Node &operator=(double value);

    /// @brief Adds `child` to the map of children at `key`.
    ///
    /// This function sets the type of the current `Node` to `Type_Object` and clears the
    /// internal data (`std::string`).
    ///
    /// @param key The key.
    /// @param child The child `Node`.
    /// @return A reference to the current `Node`.
    Node &AddChild(const std::string &key, const Node &child);

    /// @brief Appends `child` to the vector of array elements.
    ///
    /// This function sets the type of the current `Node` to `Type_Array` and clears the
    /// internal data (`std::string`).
    ///
    /// @param child The child `Node`.
    /// @return A reference to the current `Node`.
    Node &AddElement(const Node &child);

    /// @brief Gets the `Node` type.
    /// @return The `Node` type.
    Type GetType() const;

    /// @brief Checks if the type of the current `Node` is `Type_Object` and if a child is
    /// present at `key`.
    /// @param key The key.
    /// @return `true` if the current `Node` has a child at `key`, `false` otherwise.
    bool Has(const std::string &key) const;

    /// @brief Gets the size of the vector of array elements.
    ///
    /// This function returns 0 if the current `Node` is not of type `Type_Array`.
    ///
    /// @return The size of the vector of array elements.
    size_t Size() const;

    /// @brief Gets the children map.
    /// @return A reference to the children map.
    std::unordered_map<std::string, Node> &GetChildren();

    /// @brief Gets the children map (const version).
    /// @return A const reference to the children map.
    const std::unordered_map<std::string, Node> &GetChildren() const;

    /// @brief Gets the vector of array elements.
    /// @return A reference to the vector of array elements.
    std::vector<Node> &GetArrayElements();

    /// @brief Gets the vector of array elements (const version).
    /// @return A const reference to the vector of array elements.
    const std::vector<Node> &GetArrayElements() const;

private:
    Node *m_pParent;
    std::string m_Data;
    std::unordered_map<std::string, Node> m_Children;
    std::vector<Node> m_ArrayElements;
    Type m_Type;

    friend Node Parse(const std::string &data);

    friend std::string Stringify(const Node &node);

    static Type TokenTypeToNodeType(JSONTOKENTYPE tokenType);
};

/// @brief Parses `data` as a JSON tree and returns the root `Node`.
/// @param data The JSON-formatted `std::string`.
/// @return The root `Node` resulting from the parsing.
Node Parse(const std::string &data);

/// @brief Converts a JSON tree into a JSON-formatted `std::string`.
/// @param node The root `Node`.
/// @return The JSON-formatted `std::string`.
std::string Stringify(const Node &node);

}
}
