#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  class TiledMap;

  class TMR_API TileMapReader
  {
  public:

    TileMapReader();
    ~TileMapReader();

    TiledMap* readFromFile(const char* filePath);
  };
}