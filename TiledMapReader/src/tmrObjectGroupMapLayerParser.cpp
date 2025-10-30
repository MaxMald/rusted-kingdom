#include "TMR/tmrObjectGroupMapLayerParser.h"
#include "TMR/tmrObjectGroupMapLayer.h"

namespace tmr
{
  ObjectGroupMapLayerParser::ObjectGroupMapLayerParser()
  {
  }

  ObjectGroupMapLayerParser::~ObjectGroupMapLayerParser()
  {
  }

  ObjectGroupMapLayer* ObjectGroupMapLayerParser::parseFromJson(
    const std::int32_t id,
    const std::int32_t x,
    const std::int32_t y,
    const bool& visible,
    const float& opacity,
    const char* name,
    const Json& json
  )
  {
    return new ObjectGroupMapLayer(
      id,
      x, y,
      visible,
      opacity,
      name
    );
  }
}