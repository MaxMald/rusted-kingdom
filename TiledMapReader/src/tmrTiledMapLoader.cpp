#include "TMR/tmrTiledMapLoader.h"
#include "TMR/tmrTiledMapXmlLoader.h"

namespace tmr
{
  namespace tiledMapLoader
  {
    TiledMap* loadFromFile(const char* filePath)
    {
      return tiledMapXmlLoader::loadFromFile(filePath);
    }
  }
}