#pragma once

#include <cstdint>

namespace tmr
{
  namespace mapLayerType
  {
    /**
     * @enum Type
     * @brief Represents the type of a layer in a Tiled map.
     */
    enum Type : std::uint8_t
    {
      TileLayer,    ///< A layer containing tile data.
      ObjectGroup   ///< A layer containing objects.
    };
  }
}