#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  class TiledMap;

  namespace tiledMapLoader
  {
    TMR_API TiledMap* loadFromFile(const char* filePath);
  }
}