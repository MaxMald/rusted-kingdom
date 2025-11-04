#pragma once

#include <cstdint>

namespace tmr
{
  namespace TileSetType
  {
    enum Type : std::uint8_t
    {
      Unknown = 0,
      SpriteSheet,
      ImageCollection
    };
  }
}