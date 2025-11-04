#pragma once

#include <cstdint>

namespace tmr
{
  namespace tileSetType
  {
    enum Type : std::uint8_t
    {
      Unknown = 0,
      Reference,
      SpriteSheet,
      ImageCollection
    };
  }
}