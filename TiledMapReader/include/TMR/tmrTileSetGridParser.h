#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"

namespace tmr
{
  class TileSetGrid;

  class TileSetGridParser
  {
  public:

    TileSetGridParser();
    ~TileSetGridParser();

    TileSetGrid* parseFromJson(const Json& json);
  };
}