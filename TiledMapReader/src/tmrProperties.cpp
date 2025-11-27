#include "TMR/tmrProperties.h"

#include <stdexcept>

namespace tmr
{
  Properties::Properties(Property** properties, size_t propertyCount) :
    m_properties(properties),
    m_propertyCount(propertyCount)
  {
  }

  Properties::~Properties()
  {
    if (m_properties)
    {
      for (size_t i = 0; i < m_propertyCount; ++i)
        delete m_properties[i];

      delete[] m_properties;
      m_properties = nullptr;
    }
  }

  Property* Properties::getPropertyAt(size_t index) const
  {
    if (index >= m_propertyCount)
      throw std::out_of_range("Properties::getPropertyAt: index out of range");

    return m_properties[index];
  }
}