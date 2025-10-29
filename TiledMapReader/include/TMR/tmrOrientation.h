#pragma once

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
      Isometric /// Diamond-shaped tiles for isometric projection.
    };
  }
}