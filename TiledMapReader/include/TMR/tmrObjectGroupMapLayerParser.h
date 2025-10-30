#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"

namespace tmr
{
  class ObjectGroupMapLayer;

  class ObjectGroupMapLayerParser
  {
  public:
    ObjectGroupMapLayerParser();
    ~ObjectGroupMapLayerParser();

    /**
     * @brief Parse a object group layer from JSON and return a new
     * ObjectGroupMapLayer.
     *
     * @param id Layer id.
     * @param x Layer x offset.
     * @param y Layer y offset.
     * @param visible Visibility flag.
     * @param opacity Layer opacity.
     * @param name Layer name (null-terminated).
     * @param json JSON object describing the layer.
     *
     * @return Pointer to a newly allocated ObjectGroupMapLayer. Ownership is
     * transferred to the caller.
     *
     * @throws std::runtime_error on missing/invalid JSON fields.
     */
    ObjectGroupMapLayer* parseFromJson(
      const std::int32_t id,
      const std::int32_t x,
      const std::int32_t y,
      const bool& visible,
      const float& opacity,
      const char* name,
      const Json& json
    );
  };
}