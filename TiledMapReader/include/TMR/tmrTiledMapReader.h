#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  class TiledMap;
  class TiledMapParser;

  class TMR_API TileMapReader
  {
  public:

    TileMapReader();
    ~TileMapReader();

    TiledMap* readFromFile(const char* filePath);

  private:

    TiledMapParser* m_parser;
  };
}