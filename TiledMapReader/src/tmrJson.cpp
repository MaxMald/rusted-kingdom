#include "TMR/tmrJson.h"

#include <fstream>
#include <sstream>
#include <json.hpp>

namespace tmr
{
  /**
   * @brief Private implementation struct for the Json class (PIMPL idiom).
   *
   * This struct encapsulates the actual JSON data using nlohmann::json. It is
   * used to hide third-party dependencies and internal details from the public
   * interface of the Json class, ensuring ABI stability and reducing
   * compile-time dependencies.
   *
   * Members:
   *   - json: The underlying nlohmann::json object that stores all JSON data.
   *
   * Constructors:
   *   - Impl(): Default constructor, initializes an empty JSON object.
   *   - Impl(const nlohmann::json& j): Initializes from a copy of a JSON object.
   *   - Impl(nlohmann::json&& j): Initializes from a moved JSON object.
   */
  struct Json::Impl
  {
    nlohmann::json json;

    Impl() = default;

    Impl(const nlohmann::json& j) :
      json(j)
    {
    }

    Impl(nlohmann::json&& j) :
      json(std::move(j))
    {
    }
  };

  Json::Json() :
    m_impl(new Impl())
  {
  }

  Json::Json(const Json& other) :
    m_impl(new Impl(other.m_impl->json))
  {
  }

  Json::Json(Json&& other) noexcept :
    m_impl(other.m_impl)
  {
    other.m_impl = nullptr;
  }

  Json::Json(Impl* impl) :
    m_impl(impl)
  {
  }

  Json::~Json()
  {
    delete m_impl;
  }

  Json Json::parse(const char* jsonString)
  {
    nlohmann::json j = nlohmann::json::parse(jsonString);
    return Json(new Impl(std::move(j)));
  }

  Json Json::loadFromFile(const char* filePath)
  {
    std::ifstream file(filePath);

    if (!file.is_open())
    {
      throw std::runtime_error("Failed to open JSON file.");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    nlohmann::json j = nlohmann::json::parse(buffer.str());
    return Json(new Impl(std::move(j)));
  }

  Json& Json::operator=(const Json& other)
  {
    if (this != &other)
    {
      *m_impl = *other.m_impl;
    }
    return *this;
  }

  Json& Json::operator=(Json&& other) noexcept
  {
    if (this != &other)
    {
      delete m_impl;
      m_impl = other.m_impl;
      other.m_impl = nullptr;
    }
    return *this;
  }

  Json Json::operator[](const char* key) const
  {
    if (!m_impl->json.contains(key))
    {
      throw std::out_of_range("Key not found in Json object");
    }

    return Json(new Impl(m_impl->json.at(key)));
  }

  Json Json::operator[](std::size_t index) const
  {
    if (!m_impl->json.is_array() || index >= m_impl->json.size())
    {
      throw std::out_of_range("Index out of range for Json array");
    }

    return Json(new Impl(m_impl->json.at(index)));
  }

  bool Json::contains(const char* key) const
  {
    return m_impl->json.contains(key);
  }

  bool Json::isNull() const
  {
    return m_impl->json.is_null();
  }

  bool Json::isObject() const
  {
    return m_impl->json.is_object();
  }

  bool Json::isArray() const
  {
    return m_impl->json.is_array();
  }

  bool Json::isString() const
  {
    return m_impl->json.is_string();
  }

  bool Json::isNumber() const
  {
    return m_impl->json.is_number();
  }

  bool Json::isBoolean() const
  {
    return m_impl->json.is_boolean();
  }

  std::size_t Json::getStringLength() const
  {
    return m_impl->json.get<std::string>().length();
  }

  std::size_t Json::getSize() const
  {
    return m_impl->json.size();
  }

  void Json::getString(char* buffer, const std::size_t& bufferSize) const
  {
    if (bufferSize == 0)
      return;

    std::string str = m_impl->json.get<std::string>();
    std::size_t len = str.length();

    if (bufferSize < len + 1)
    {
      throw std::runtime_error(
        "Buffer size is insufficient for the string value."
      );
    }

    std::strncpy(buffer, str.c_str(), bufferSize - 1);
    buffer[bufferSize - 1] = '\0';
  }

  void Json::getArrayInt32(
    std::int32_t* outArray,
    const std::size_t& arraySize
  ) const
  {
    if (!m_impl->json.is_array())
    {
      throw std::runtime_error("JSON value is not an array.");
    }

    const auto& jsonArray = m_impl->json;
    if (jsonArray.size() < arraySize)
    {
      throw std::runtime_error(
        "JSON array size is smaller than the provided array size."
      );
    }

    for (std::size_t i = 0; i < arraySize; ++i)
    {
      if (!jsonArray[i].is_number_integer())
      {
        throw std::runtime_error(
          "JSON array contains non-integer elements."
        );
      }

      outArray[i] = static_cast<std::int32_t>(jsonArray[i].get<int>());
    }
  }

  bool Json::getBool() const
  {
    return m_impl->json.get<bool>();
  }

  std::int32_t Json::getInt32() const
  {
    return static_cast<std::int32_t>(m_impl->json.get<int>());
  }

  float Json::getFloat() const
  {
    return m_impl->json.get<float>();
  }
}