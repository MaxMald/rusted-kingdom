#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  /**
   * @brief Wrapper class for nlohmann::json providing a simplified and
   * engine-friendly JSON interface.
   */
  class Json
  {
  public:

    /**
     * @brief Default constructor. Initializes an empty JSON value.
     */
    Json();

    /**
     * @brief Copy constructor. Performs a deep copy of the JSON value.
     * 
     * @param other The Json object to copy from.
     */
    Json(const Json& other);

    /**
     * @brief Move constructor. Transfers ownership of the JSON value.
     * 
     * @param other The Json object to move from.
     */
    Json(Json&& other) noexcept;

    /**
     * @brief Destructor. Cleans up internal resources.
     */
    ~Json();

    /**
     * @brief Parses a JSON string and returns a Json object.
     * 
     * @param jsonString The string containing JSON data.
     * 
     * @return A Json object representing the parsed data.
     * 
     * @throws nlohmann::json::parse_error if the input is not valid JSON.
     */
    static Json parse(const String& jsonString);

    /**
     * @brief Loads JSON data from a file and returns a Json object.
     *
     * @param filePath The path to the JSON file.
     *
     * @return A Json object representing the loaded data.
     *
     * @throws RuntimeErrorException if the file cannot be opened.
     * @throws LogicErrorException if the file content is not valid JSON.
     */
    static Json loadFromFile(const String& filePath);

    /**
     * @brief Copy assignment operator. Performs a deep copy of the JSON value.
     *
     * @param other The Json object to copy from.
     *
     * @return Reference to this Json object.
     */
    Json& operator=(const Json& other);

    /**
     * @brief Move assignment operator. Transfers ownership of the JSON value.
     *
     * @param other The Json object to move from.
     *
     * @return Reference to this Json object.
     */
    Json& operator=(Json&& other) noexcept;

    /**
     * @brief Accesses a JSON object member by key.
     * 
     * @param key The key of the member to access.
     * 
     * @return A Json object representing the value at the given key.
     * 
     * @throws std::out_of_range if the key does not exist.
     */
    Json operator[](const String& key) const;

    /**
     * @brief Accesses a JSON array element by index.
     * 
     * @param index The index of the element to access.
     * 
     * @return A Json object representing the value at the given index.
     * 
     * @throws std::out_of_range if the index is out of bounds.
     */
    Json operator[](SizeT index) const;

    /**
     * @brief Checks if a key exists in the JSON object.
     * 
     * @param key The key to check.
     * 
     * @return True if the key exists, false otherwise.
     */
    Bool contains(const String& key) const;

    /**
     * @brief Checks if the JSON value is null.
     * 
     * @return True if the value is null, false otherwise.
     */
    Bool isNull() const;

    /**
     * @brief Checks if the JSON value is an object.
     * 
     * @return True if the value is an object, false otherwise.
     */
    Bool isObject() const;

    /**
     * @brief Checks if the JSON value is an array.
     * 
     * @return True if the value is an array, false otherwise.
     */
    Bool isArray() const;

    /**
     * @brief Checks if the JSON value is a string.
     * 
     * @return True if the value is a string, false otherwise.
     */
    Bool isString() const;

    /**
     * @brief Checks if the JSON value is a number.
     * 
     * @return True if the value is a number, false otherwise.
     */
    Bool isNumber() const;

    /**
     * @brief Checks if the JSON value is a boolean.
     * 
     * @return True if the value is a boolean, false otherwise.
     */
    Bool isBoolean() const;

    /**
     * @brief Returns the value as a String.
     * @return The string value.
     * @throws std::exception if the value is not a string.
     */
    String getString() const;

    /**
     * @brief Returns the value as a boolean.
     * @return The boolean value.
     * @throws std::exception if the value is not a boolean.
     */
    Bool getBool() const;

    /**
     * @brief Returns the value as a 32-bit integer.
     * @return The integer value.
     * @throws std::exception if the value is not a number.
     */
    Int32 getInt32() const;
   

  private:

    /**
     * @brief Private implementation struct for the Json class (PIMPL idiom).
     *
     * This struct is defined in the source file and encapsulates all internal data
     * and third-party dependencies, such as nlohmann::json. It is used to ensure
     * ABI stability and hide implementation details from the public interface.
     */
    struct Impl;

    /**
     * @brief Pointer to the private implementation.
     */
    Impl* m_impl;

    /**
     * @brief Internal constructor used for constructing from an implementation
     * pointer.
     * 
     * @param impl Pointer to the implementation struct.
     */
    Json(Impl* impl);
  };
}