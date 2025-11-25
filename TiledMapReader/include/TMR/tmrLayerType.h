#pragma once

#include <cstdint>

namespace tmr
{
  namespace layerType
  {
    /**
     * @enum Type
     * @brief Represents the type of a layer in a Tiled map.
     */
    enum Type : std::uint8_t
    {
      Undefined = 0,
      GridData = 1,
      ObjectGroup = 2
    };
  }
}