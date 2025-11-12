#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  template<typename T>
  class BlackboardValueGroup
  {
  public:
    BlackboardValueGroup() = default;
    ~BlackboardValueGroup() = default;

    BlackboardValueGroup(const BlackboardValueGroup&) = delete;
    BlackboardValueGroup& operator=(const BlackboardValueGroup&) = delete;
    BlackboardValueGroup(BlackboardValueGroup&&) noexcept = delete;
    BlackboardValueGroup& operator=(BlackboardValueGroup&&) noexcept = delete;

    bool hasValue(const String& key) const
    {
      return m_values.find(key) != m_values.end();
    }

    T getValue(const String& key) const
    {
      auto it = m_values.find(key);
      if (it != m_values.end())
        return it->second;

      throw OutOfRangeException(
        String::Format(
          "BlackboardValueGroup error: Key '%s' not found.",
          key.c_str()
        )
      );
    }

    void setValue(const String& key, const T& value)
    {
      m_values[key] = value;
    }

  private:
    UnorderedMap<String, T> m_values;
  };
}