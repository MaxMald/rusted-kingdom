#include "TMR/tmrObjectGroup.h"

#include <cstring>

#include "TMR/tmrObject.h"

namespace tmr
{
  ObjectGroup::ObjectGroup(
    const std::int32_t& id,
    const char* name,
    const drawOrder::Type& drawOrder,
    Object** objects,
    const std::size_t objectsSize
  ) :
    m_objects(objects),
    m_objectsSize(objectsSize),
    m_id(id),
    m_drawOrder(drawOrder)
  {
    m_name = name ? new char[strlen(name) + 1] : nullptr;
    if (m_name)
      strcpy(m_name, name);
  }

  ObjectGroup::~ObjectGroup()
  {
    if (m_name)
    {
      delete[] m_name;
      m_name = nullptr;
    }

    if (m_objects)
    {
      for (std::size_t i = 0; i < m_objectsSize; ++i)
        delete m_objects[i];
      delete[] m_objects;

      m_objects = nullptr;
      m_objectsSize = 0;
    }
  }
}