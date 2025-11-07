#include "TMR/tmrObjectGroupMapLayer.h"
#include "TMR/tmrObject.h"

namespace tmr
{
  ObjectGroupMapLayer::ObjectGroupMapLayer(
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
    MapLayer(
      mapLayerType::ObjectGroup,
      id,
      x,
      y,
      visible,
      opacity,
      name
    ),
    m_drawOrder(drawOrder),
    m_objects(objects),
    m_objectsSize(objectsSize)
  {
  }

  ObjectGroupMapLayer::~ObjectGroupMapLayer()
  {
    for (std::uint32_t i = 0; i < m_objectsSize; ++i)
      delete m_objects[i];

    delete[] m_objects;
    m_objects = nullptr;
  }
}