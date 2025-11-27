#include "TMR/tmrStringProperty.h"

#include <string>

namespace tmr
{
  StringProperty::StringProperty(const char* name, const char* value) :
    Property(name, propertyType::Type::String)
  {
    m_value = value ? new char[std::strlen(value) + 1] : nullptr;
    if (m_value)
      std::strcpy(m_value, value);
  }

  StringProperty::~StringProperty()
  {
    if (m_value)
    {
      delete[] m_value;
      m_value = nullptr;
    }
  }
}