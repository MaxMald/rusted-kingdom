#include "TMR/tmrObjectGroup.h"
#include <cstring>
#include "TMR/tmrObject.h"

namespace tmr
{
  ObjectGroup::ObjectGroup(
    const std::int32_t& id,
    const std::int32_t& x,
    const std::int32_t& y,
    const bool& visible,
    const float& opacity,
    const char* name,
    const drawOrder::Type drawOrder,
    Object** objects,
    const std::size_t objectsSize
  ) :
    m_drawOrder(drawOrder),
    m_objects(objects),
    m_objectsSize(objectsSize),
    m_id(id),
    m_x(x),
    m_y(y),
    m_visible(visible),
    m_opacity(opacity)
  {
    m_name = name ? new char[strlen(name) + 1] : nullptr;
    if (m_name)
      strcpy(m_name, name);
  }

  ObjectGroup::~ObjectGroup()
  {
    delete[] m_name;
    for (std::size_t i = 0; i < m_objectsSize; ++i)
      delete m_objects[i];

    delete[] m_objects;
  }
}