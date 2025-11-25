#include "rkTiledMap.h"

#include <TMR/tmrTiledMap.h>
#include <TMR/tmrTileSet.h>
#include <TMR/tmrTiledMapLoader.h>

namespace rk
{
  TiledMap::TiledMap() :
    m_tmrTiledMap(nullptr)
  {
  }

  TiledMap::~TiledMap()
  {
  }

  bool TiledMap::loadFromFile(const Path& filename)
  {
    try
    {
      tmr::TiledMap* loadedTiledMap = tmr::tiledMapLoader::loadFromFile(
        filename.string().c_str()
      );

      if (!loadedTiledMap)
        return false;

      m_tmrTiledMap = loadedTiledMap;
    }
    catch (const std::exception&)
    {
      unload();
      return false;
    }
    catch (...)
    {
      unload();
      return false;
    }

    return true;
  }

  void TiledMap::unload()
  {
    if (m_tmrTiledMap)
    {
      delete m_tmrTiledMap;
      m_tmrTiledMap = nullptr;
    }
  }
}