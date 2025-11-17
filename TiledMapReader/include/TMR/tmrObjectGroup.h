#pragma once

#include "TMR/tmrDrawOrder.h"

namespace tmr
{
  class Object;

  class TMR_API ObjectGroup
  {
  public:
    ObjectGroup(
      const std::int32_t& id,
      const std::int32_t& x,
      const std::int32_t& y,
      const bool& visible,
      const float& opacity,
      const char* name,
      const drawOrder::Type drawOrder,
      Object** objects,
      const std::size_t objectsSize
    );
    virtual ~ObjectGroup();

    const drawOrder::Type& getDrawOrder() const { return m_drawOrder; }
    const Object* getObjectAt(const std::uint32_t& index) const { return m_objects[index]; }
    std::size_t getObjectSize() const { return m_objectsSize; }
    std::int32_t getId() const { return m_id; }
    std::int32_t getX() const { return m_x; }
    std::int32_t getY() const { return m_y; }
    bool isVisible() const { return m_visible; }
    float getOpacity() const { return m_opacity; }
    const char* getName() const { return m_name; }

  private:
    drawOrder::Type m_drawOrder;    /// < The draw order of the objects in the group.
    Object** m_objects;             /// < The array of objects in the group.
    std::size_t m_objectsSize;      /// < The number of objects in the group.
    std::int32_t m_id;              ///< The unique identifier for the layer.
    std::int32_t m_x;               ///< The x-coordinate of the layer.
    std::int32_t m_y;               ///< The y-coordinate of the layer.
    bool m_visible;                 ///< Whether the layer is visible.
    float m_opacity;                ///< The opacity of the layer.
    char* m_name;                   ///< The name of the layer.
  };
}