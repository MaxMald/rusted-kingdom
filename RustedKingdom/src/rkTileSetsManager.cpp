#include "rkTileSetsManager.h"
#include <TMR/tmrTiledMap.h>
#include "rkTileSet.h"

namespace rk
{
  TileSetsManager::TileSetsManager() :
    m_tileSets()
  {
  }

  TileSetsManager::~TileSetsManager()
  {
    clear();
  }

  bool TileSetsManager::load(
    const std::filesystem::path& mapRootDirectory,
    const tmr::TiledMap* tiledMap)
  {
    clear();

    if (!tiledMap)
      return false;

    const std::size_t count = tiledMap->getTileSetsCount();
    for (std::size_t i = 0; i < count; ++i)
    {
      const tmr::TileSet* tmrTileSet = tiledMap->getTileSetAt(i);
      if (!tmrTileSet)
        continue;

      TileSet* rsTileSet = new TileSet(
        mapRootDirectory,
        const_cast<tmr::TileSet*>(tmrTileSet)
      );

      m_tileSets.push_back(rsTileSet);
    }

    return true;
  }

  void TileSetsManager::clear()
  {
    for (TileSet* ts : m_tileSets)
      delete ts;

    m_tileSets.clear();
  }
}