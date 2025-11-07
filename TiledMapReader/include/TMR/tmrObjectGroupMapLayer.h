#pragma once

#include "TMR/tmrMapLayer.h"
#include "TMR/tmrDrawOrder.h"

namespace tmr
{
  class Object;

  class TMR_API ObjectGroupMapLayer : public MapLayer
  {
  public:
    ObjectGroupMapLayer(
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
    virtual ~ObjectGroupMapLayer();

    const drawOrder::Type& getDrawOrder() const { return m_drawOrder; }
    Object* getObjectAt(const std::uint32_t& index) { return m_objects[index]; }
    std::size_t getObjectSize() const { return m_objectsSize; }

  private:
    drawOrder::Type m_drawOrder;
    Object** m_objects;
    std::size_t m_objectsSize;
  };
}
