#pragma once

#include "tmrPrerequisites.h"

namespace tmr
{
  /**
   * @enum Type
   *
   * @brief Represents the orientation of a Tiled map.
   */
  namespace orientation
  {
    enum class Type : std::uint8_t
    {
      Undefined = 0,
      Isometric = 1,  /// Diamond-shaped tiles for isometric projection.
      Orthogonal = 2, /// Standard grid of square tiles.
    };
  }
}