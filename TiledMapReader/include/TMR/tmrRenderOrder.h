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
      RightDown, ///< Layers are rendered from right to left, then top to bottom.
      RightUp,   ///< Layers are rendered from right to left, then bottom to top.
      LeftDown,  ///< Layers are rendered from left to right, then top to bottom.
      LeftUp     ///< Layers are rendered from left to right, then bottom to top.
    };
  }
}