#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  class TiledMap;
  class TiledMapParser;

  class TMR_API TiledMapReader
  {
  public:

    TiledMapReader();
    ~TiledMapReader();

    TiledMap* readFromFile(const char* filePath);

  private:

    TiledMapParser* m_parser;
  };
}