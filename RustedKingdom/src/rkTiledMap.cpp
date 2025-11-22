#include "rkTiledMap.h"

#include <TMR/tmrTiledMapReader.h>
#include <TMR/tmrTiledMap.h>
#include <TMR/tmrTileSet.h>
#include <TMR/tmrTileSetsEmbedder.h>

namespace rk
{
  TiledMap::TiledMap() :
    m_tmrTiledMap(nullptr),
    m_tiledMapFilename()
  {
  }

  TiledMap::~TiledMap()
  {
  }

  bool TiledMap::loadFromFile(const Path& filename)
  {
    try
    {
      tmr::TiledMapReader tiledMapReader;
      tmr::TiledMap* loadedTiledMap = tiledMapReader.readFromFile(
        filename.string().c_str()
      );

      String tiledMapfolder = filename.parent_path().string();
      tmr::tileSetsEmbedder::embedTileSets(
        *loadedTiledMap,
        tiledMapfolder.c_str()
      );

      if (!loadedTiledMap)
        return false;

      m_tmrTiledMap = loadedTiledMap;
      m_tiledMapFilename = filename;
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

    m_tiledMapFilename = Path();
  }
}