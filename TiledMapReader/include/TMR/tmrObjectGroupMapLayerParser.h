#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"
#include "TMR/tmrObjectParser.h"

namespace tmr
{
  class ObjectGroupMapLayer;

  class ObjectGroupMapLayerParser
  {
  public:
    ObjectGroupMapLayerParser();
    ~ObjectGroupMapLayerParser();

    ObjectGroupMapLayer* parseFromJson(
      const std::int32_t id,
      const std::int32_t x,
      const std::int32_t y,
      const bool& visible,
      const float& opacity,
      const char* name,
      const Json& json
    );

    ObjectGroupMapLayer* parseFromJson(const Json& json);

  private:
    ObjectParser m_objectParser;
  };
}