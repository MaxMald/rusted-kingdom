#include "TMR/tmrObject.h"

#include <memory>

#include "TMR/tmrProperties.h"

namespace tmr
{
  Object::Object(
    objectType::Type objectType,
    uint32_t id,
    float x,
    float y,
    bool visible,
    const char* name,
    const char* type,
    Properties* properties
  ) :
    m_objectType(objectType),
    m_id(id),
    m_visible(visible),
    m_x(x),
    m_y(y),
    m_properties(properties)
  {
    m_name = name ? new char[std::strlen(name) + 1] : nullptr;
    if (m_name)
      std::strcpy(m_name, name);

    m_type = type ? new char[std::strlen(type) + 1] : nullptr;
    if (m_type)
      std::strcpy(m_type, type);
  }

  Object::~Object()
  {
    delete[] m_name;
    delete[] m_type;
    delete m_properties;
  }
}