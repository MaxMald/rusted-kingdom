#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
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
    static Json parse(const char* jsonString);

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
    static Json loadFromFile(const char* filePath);

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
    Json operator[](const char* key) const;

    /**
     * @brief Accesses a JSON array element by index.
     *
     * @param index The index of the element to access.
     *
     * @return A Json object representing the value at the given index.
     *
     * @throws std::out_of_range if the index is out of bounds.
     */
    Json operator[](std::size_t index) const;

    /**
     * @brief Checks if a key exists in the JSON object.
     *
     * @param key The key to check.
     *
     * @return True if the key exists, false otherwise.
     */
    bool contains(const char* key) const;

    /**
     * @brief Checks if the JSON value is null.
     *
     * @return True if the value is null, false otherwise.
     */
    bool isNull() const;

    /**
     * @brief Checks if the JSON value is an object.
     *
     * @return True if the value is an object, false otherwise.
     */
    bool isObject() const;

    /**
     * @brief Checks if the JSON value is an array.
     *
     * @return True if the value is an array, false otherwise.
     */
    bool isArray() const;

    /**
     * @brief Checks if the JSON value is a string.
     *
     * @return True if the value is a string, false otherwise.
     */
    bool isString() const;

    /**
     * @brief Checks if the JSON value is a number.
     *
     * @return True if the value is a number, false otherwise.
     */
    bool isNumber() const;

    /**
     * @brief Checks if the JSON value is a boolean.
     *
     * @return True if the value is a boolean, false otherwise.
     */
    bool isBoolean() const;

    /**
     * @brief Returns the length of the JSON string value, excluding the null
     * terminator.
     *
     * This method returns the number of characters in the string value stored in
     * the JSON object. If you need to allocate a buffer for the string
     * (including the null terminator), use getStringLength() + 1 as the required
     * buffer size.
     *
     * @return The length of the string value, not including the null terminator.
     * 
     * @throws std::exception if the value is not a string.
     */
    std::size_t getStringLength() const;

    /**
     * @brief Copies the JSON string value into a caller-provided buffer.
     *
     * Copies up to bufferSize - 1 characters from the string value to the buffer
     * and ensures null-termination. The buffer must be large enough to hold the
     * string and the null terminator. Use getStringLength() + 1 to determine the
     * required buffer size.
     *
     * @param buffer Pointer to the destination buffer.
     * @param bufferSize Size of the destination buffer in bytes.
     *
     * @throws std::exception if the value is not a string.
     */
    void getString(char* buffer, std::size_t bufferSize) const;

    /**
     * @brief Returns the value as a boolean.
     * @return The boolean value.
     * @throws std::exception if the value is not a boolean.
     */
    bool getBool() const;

    /**
     * @brief Returns the value as a 32-bit integer.
     * @return The integer value.
     * @throws std::exception if the value is not a number.
     */
    std::int32_t getInt32() const;


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
