#include "rkTiledMap.h"
#include <TMR/tmrTiledMapReader.h>
#include <TMR/tmrTiledMap.h>
#include <TMR/tmrTileSet.h>

namespace rk
{
  TiledMap::TiledMap() :
    m_tmrTiledMap(nullptr),
    m_tileSetsManager()
  {

  }

  TiledMap::~TiledMap()
  {
    clear();
  }

  bool TiledMap::loadFromFile(const Path& filename)
  {
    clear();

    try
    {
      tmr::TiledMapReader tiledMapReader;
      tmr::TiledMap* loadedTiledMap = tiledMapReader.readFromFile(
        filename.string().c_str()
      );

      if (!loadedTiledMap)
        return false;

      m_tmrTiledMap = loadedTiledMap;

      Path rootDirectory = filename.parent_path();
      m_tileSetsManager.load(rootDirectory, loadedTiledMap);
    }
    catch (const std::exception& /*e*/)
    {
      clear();
      return false;
    }
    catch (...)
    {
      clear();
      return false;
    }

    return true;
  }

  void TiledMap::clear()
  {
    if (m_tmrTiledMap)
    {
      delete m_tmrTiledMap;
      m_tmrTiledMap = nullptr;
    }

    m_tileSetsManager.clear();
  }
}