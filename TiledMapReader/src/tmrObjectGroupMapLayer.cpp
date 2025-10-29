#include "TMR/tmrObjectGroupMapLayer.h"

namespace tmr
{
  ObjectGroupMapLayer::ObjectGroupMapLayer(
    const std::int32_t& id,
    const std::int32_t& x,
    const std::int32_t& y,
    const bool& visible,
    const float& opacity,
    const char* name) :
    MapLayer(
      mapLayerType::ObjectGroup,
      id,
      x,
      y,
      visible,
      opacity,
      name
    )
  {
  }

  ObjectGroupMapLayer::~ObjectGroupMapLayer()
  {
  }
}