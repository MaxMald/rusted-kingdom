#pragma once

#include "TMR/tmrMapLayer.h"

namespace tmr
{
  class TMR_API ObjectGroupMapLayer : public MapLayer
  {
  public:

    /**
     * @brief Constructs an ObjectGroupMapLayer with the specified properties.
     *
     * @param id The unique identifier for the layer.
     * @param x The x-coordinate of the layer.
     * @param y The y-coordinate of the layer.
     * @param visible Whether the layer is visible.
     * @param opacity The opacity of the layer (0.0f to 1.0f).
     * @param name The name of the layer.
     */
    ObjectGroupMapLayer(
      const std::int32_t& id,
      const std::int32_t& x,
      const std::int32_t& y,
      const bool& visible,
      const float& opacity,
      const char* name
    );
    virtual ~ObjectGroupMapLayer();
  };
}
