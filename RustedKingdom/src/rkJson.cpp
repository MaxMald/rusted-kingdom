#include "rkJson.h"

#include <fstream>
#include <sstream>
#include <JSON/json.hpp>

namespace rk
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

  Json Json::parse(const String& jsonString)
  {
    nlohmann::json j = nlohmann::json::parse(jsonString.c_str());
    return Json(new Impl(std::move(j)));
  }

  Json Json::loadFromFile(const String& filePath)
  {
    std::ifstream file(filePath.c_str());

    if (!file.is_open())
    {
      throw RuntimeErrorException(
        String::Format("Failed to open JSON file: %s", filePath.c_str())
      );
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    try
    {
      nlohmann::json j = nlohmann::json::parse(buffer.str());
      return Json(new Impl(std::move(j)));
    }
    catch (const nlohmann::json::parse_error& e)
    {
      throw LogicErrorException(
        String::Format(
          "JSON parse error in file '%s': %s", 
          filePath.c_str(), 
          e.what()
        )
      );
    }
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

  Json Json::operator[](const String& key) const
  {
    if (!m_impl->json.contains(key.c_str()))
    {
      throw OutOfRangeException(
        String::Format("Key '%s' not found in JSON object.", key.c_str())
      );
    }
    return Json(new Impl(m_impl->json.at(key.c_str())));
  }

  Json Json::operator[](SizeT index) const
  {
    if (!m_impl->json.is_array() || index >= m_impl->json.size())
    {
      throw OutOfRangeException(
        String::Format("Index %zu is out of range for JSON array.", index)
      );
    }
    return Json(new Impl(m_impl->json.at(index)));
  }

  Bool Json::contains(const String& key) const
  {
    return m_impl->json.contains(key.c_str());
  }

  Bool Json::isNull() const
  {
    return m_impl->json.is_null();
  }

  Bool Json::isObject() const
  {
    return m_impl->json.is_object();
  }

  Bool Json::isArray() const
  {
    return m_impl->json.is_array();
  }

  Bool Json::isString() const
  {
    return m_impl->json.is_string();
  }

  Bool Json::isNumber() const
  {
    return m_impl->json.is_number();
  }

  Bool Json::isBoolean() const
  {
    return m_impl->json.is_boolean();
  }

  String Json::getString() const
  {
    return String(m_impl->json.get<std::string>().c_str());
  }

  Bool Json::getBool() const
  {
    return m_impl->json.get<bool>();
  }

  Int32 Json::getInt32() const
  {
    return static_cast<Int32>(m_impl->json.get<int>());
  }
}