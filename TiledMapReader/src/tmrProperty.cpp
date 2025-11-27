#include "TMR/tmrProperty.h"

#include <string>

namespace tmr
{
  Property::Property(
    const char* name,
    propertyType::Type type
  )
    : m_type(type)
  {
    m_name = name ? new char[std::strlen(name) + 1] : nullptr;
    if (m_name)
      std::strcpy(m_name, name);
  }

  Property::~Property()
  {
    if (m_name)
    {
      delete[] m_name;
      m_name = nullptr;
    }
  }
}