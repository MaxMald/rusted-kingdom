#include "TMR/tmrFileProperty.h"

#include <string>

namespace tmr
{
  FileProperty::FileProperty(const char* name, const char* value) :
    Property(name, propertyType::Color)
  {
    m_value = value ? new char[std::strlen(value) + 1] : nullptr;
    if (m_value)
      std::strcpy(m_value, value);
  }

  FileProperty::~FileProperty()
  {
    if (m_value)
    {
      delete[] m_value;
      m_value = nullptr;
    }
  }
}