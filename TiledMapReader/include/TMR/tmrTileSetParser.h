#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"
#include "TMR/tmrSpriteSheetTileSetParser.h"

namespace tmr
{
  class TileSet;

  class TileSetParser
  {
  public:
    TileSetParser();
    ~TileSetParser();

    TileSet* parseFromJson(const Json& json);

  private:
    SpriteSheetTileSetParser m_spriteSheetTileSetParser;
  };
}