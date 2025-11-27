#include "TMR/tmrColorProperty.h"

#include <string>

namespace tmr
{
  ColorProperty::ColorProperty(const char* name, const char* value): 
    Property(name, propertyType::Color)
  {
    m_value = value ? new char[std::strlen(value) + 1] : nullptr;
    if (m_value)
      std::strcpy(m_value, value);
  }

  ColorProperty::~ColorProperty()
  {
    if (m_value)
    {
      delete[] m_value;
      m_value = nullptr;
    }
  }
}