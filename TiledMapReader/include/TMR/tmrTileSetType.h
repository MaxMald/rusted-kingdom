#pragma once

#include <cstdint>

namespace tmr
{
  namespace TileSetType
  {
    enum Type : std::uint8_t
    {
      UNKNOWN = 0,
      TILESET,
      COLLECTION
    };
  }
}