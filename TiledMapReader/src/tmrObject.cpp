#include "TMR/tmrObject.h"

#include <memory>

namespace tmr
{
  Object::Object(
    std::uint32_t gid,
    std::uint32_t id,
    std::uint32_t height,
    std::uint32_t width,
    bool visible,
    bool ellipse,
    float rotation,
    float x,
    float y,
    const char* name,
    const char* type
  ) :
    m_gid(gid),
    m_id(id),
    m_height(height),
    m_width(width),
    m_visible(visible),
    m_ellipse(ellipse),
    m_rotation(rotation),
    m_x(x),
    m_y(y)
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
  }
}