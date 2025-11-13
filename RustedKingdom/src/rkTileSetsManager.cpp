#include "rkTileSetsManager.h"
#include <TMR/tmrTiledMap.h>
#include <TMR/tmrTileSet.h>
#include <TMR/tmrReferenceTileSet.h>
#include <TMR/tmrSpriteSheetTileSet.h>
#include <TMR/tmrImageCollectionTileSet.h>
#include "rkTileSet.h"
#include "rkReferenceTileSet.h"
#include "rkSpriteSheetTileSet.h"
#include "rkImageCollectionTileSet.h"
#include "rkTileSet.h"
#include "rkAssertions.h"

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
    const tmr::TiledMap& tiledMap)
  {
    clear();

    const SizeT count = tiledMap.getTileSetsCount();
    for (SizeT i = 0; i < count; ++i)
    {
      const tmr::TileSet* tmrTileSet = tiledMap.getTileSetAt(i);
      assertions::assertNotNull(tmrTileSet, "tmrTileSet");

      m_tileSets.push_back(
        createTileSetFromTmrTileSet(mapRootDirectory, *tmrTileSet)
      );
    }

    return true;
  }

  const TileSet& TileSetsManager::getTileSetAt(const SizeT& index) const
  {
    assertions::assertIndexInRange(index, m_tileSets.size(), "Tile Set Index");
    return *(m_tileSets[index]);
  }

  TileDescription TileSetsManager::getTileDescriptionByGid(
    const Int32& gid
  ) const
  {
    for (const TileSet* tileSet : m_tileSets)
    {
      if (!tileSet->isGidInRange(gid))
        continue;

      const Int32 firstGid = tileSet->getFirstGid();
      const Int32 localId = gid - firstGid;
      return tileSet->getTileDescriptionAt(localId);
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

  TileSet* TileSetsManager::createTileSetFromTmrTileSet(
    const Path& mapRootDirectory,
    const tmr::TileSet& tmrTileSet) const
  {
    const tmr::tileSetType::Type& tileSetType = tmrTileSet.getType();
    
    if (tileSetType == tmr::tileSetType::Unknown)
    {
      throw RuntimeErrorException(
        "TileSetsManager::load: TileSet has unknown type."
      );
    }

    else if (tileSetType == tmr::tileSetType::Reference)
    {
      ReferenceTileSet* referenceTileSet = new ReferenceTileSet(
        mapRootDirectory,
        static_cast<const tmr::ReferenceTileSet&>(tmrTileSet)
      );

      return static_cast<rk::TileSet*>(referenceTileSet);
    }

    else if (tileSetType == tmr::tileSetType::SpriteSheet)
    {
      SpriteSheetTileSet* spriteSheetTileSet = new SpriteSheetTileSet(
        mapRootDirectory,
        static_cast<const tmr::SpriteSheetTileSet&>(tmrTileSet)
      );

      return static_cast<rk::TileSet*>(spriteSheetTileSet);
    }

    else if (tileSetType == tmr::tileSetType::ImageCollection)
    {
      ImageCollectionTileSet* imageCollectionTileSet = new ImageCollectionTileSet(
        mapRootDirectory,
        static_cast<const tmr::ImageCollectionTileSet&>(tmrTileSet)
      );

      return static_cast<rk::TileSet*>(imageCollectionTileSet);
    }

    else
    {
      throw RuntimeErrorException(
        "TileSetsManager::load: Unsupported TileSet type."
      );
    }
  }
}