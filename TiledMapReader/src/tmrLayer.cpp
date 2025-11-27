#include "TMR/tmrLayer.h"

#include <cstring>

#include "TMR/tmrProperties.h"

namespace tmr
{
  Layer::Layer(
    const std::int32_t& id,
    const char* name,
    Properties* properties,
    layerType::Type type
  ) :
    m_id(id),
    m_name(nullptr),
    m_properties(properties),
    m_type(type)
  {
    m_name = name ? new char[std::strlen(name) + 1] : nullptr;
    if (m_name)
      std::strcpy(m_name, name);
  }

  Layer::~Layer()
  {
    if (m_name)
    {
      delete[] m_name;
      m_name = nullptr;
    }

    if (m_properties)
    {
      delete m_properties;
      m_properties = nullptr;
    }
  }
}

