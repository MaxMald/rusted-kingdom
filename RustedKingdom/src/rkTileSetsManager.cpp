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
    const Path& mapRootDirectory,
    const tmr::TiledMap* tiledMap)
  {
    clear();

    if (!tiledMap)
      return false;

    const SizeT count = tiledMap->getTileSetsCount();
    for (SizeT i = 0; i < count; ++i)
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

  const TileSet* TileSetsManager::getTileSetAt(const SizeT& index) const
  {
    if (index >= m_tileSets.size())
      throw RuntimeErrorException(
        String::Format(
          "TileSetsManager::getTileSetAt: Index %zu is out of bounds (max %zu).",
          index,
          m_tileSets.size() - 1
        )
      );

    return m_tileSets[index];
  }

  TileDescription TileSetsManager::getTileDescriptionByGid(
    const Int32& gid
  ) const
  {
    for (const TileSet* tileSet : m_tileSets)
    {
      if (!isGidInTileSetRange(tileSet, gid))
        continue;

      const Int32 firstGid = tileSet->getFirstGid();
      const Int32 localId = gid - firstGid;

      return TileDescription(
        tileSet->getImageKey(),
        tileSet->getTileTextureRect(localId)
      );
    }

    throw RuntimeErrorException(
      String::Format(
        "TileSetsManager::getTileDescriptionByGid: GID %d not found in any loaded tileset.",
        gid
      )
    );
  }

  void TileSetsManager::clear()
  {
    for (TileSet* ts : m_tileSets)
      delete ts;

    m_tileSets.clear();
  }

  bool TileSetsManager::isGidInTileSetRange(
    const TileSet* tileSet,
    const Int32& gid
  ) const
  {
    const Int32 firstGid = tileSet->getFirstGid();
    const Int32 tileCount = static_cast<Int32>(tileSet->getTileCount());
    return (gid >= firstGid && gid < firstGid + tileCount);
  }
}