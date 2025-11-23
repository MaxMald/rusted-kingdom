#pragma once

#include "TMR/tmrNonCopyable.h"
#include "TMR/tmrDrawOrder.h"

namespace tmr
{
  class Object;

  class TMR_API ObjectGroup : public NonCopyable
  {
  public:
    ObjectGroup(
      const std::int32_t& id,
      const char* name,
      const drawOrder::Type& drawOrder,
      Object** objects,
      const std::size_t objectsSize
    );
    virtual ~ObjectGroup();

    const Object* getObjectAt(const std::uint32_t& index) const { return m_objects[index]; }
    std::size_t getObjectSize() const { return m_objectsSize; }
    std::int32_t getId() const { return m_id; }
    const char* getName() const { return m_name; }
    drawOrder::Type getDrawOrder() const { return m_drawOrder; }

  private:
    Object** m_objects;             /// < The array of objects in the group.
    std::size_t m_objectsSize;      /// < The number of objects in the group.
    std::int32_t m_id;              ///< The unique identifier for the layer.
    char* m_name;                   ///< The name of the layer.
    drawOrder::Type m_drawOrder;    ///< The draw order of the object group.
  };
}