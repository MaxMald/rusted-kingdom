#pragma once

#include "tmrPrerequisites.h"

namespace tmr
{
  /**
   * @enum Type
   *
   * @brief Represents the rendering order of layers in a Tiled map.
   */
  namespace renderOrder
  {
    enum class Type : std::uint8_t
    {
      Undefined = 0, ///< Undefined render order.
      RightDown = 1, ///< Layers are rendered from right to left, then top to bottom.
      RightUp = 2,   ///< Layers are rendered from right to left, then bottom to top.
      LeftDown = 3,  ///< Layers are rendered from left to right, then top to bottom.
      LeftUp = 4     ///< Layers are rendered from left to right, then bottom to top.
    };
  }
}