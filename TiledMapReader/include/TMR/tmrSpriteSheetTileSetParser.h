#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"

namespace tmr
{
  class SpriteSheetTileSet;

  class SpriteSheetTileSetParser
  {
  public:

    SpriteSheetTileSetParser();
    ~SpriteSheetTileSetParser();

    SpriteSheetTileSet* parseFromJson(
      const std::int32_t firstgid,
      const Json& json
    );
  };
}