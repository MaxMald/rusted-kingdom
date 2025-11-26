#include "rkTiledMapUtilities.h"

#include "TMR/tmrTiledMap.h"
#include "TMR/tmrTileSet.h"

#include "rkTiledMap.h"
#include "rkIsometricPositionTransformer.h"

namespace rk
{
  namespace tiledMapUtilities
  {
    const tmr::TileSet* getTileSetWithGid(const tmr::TiledMap* tiledMap, Int32 gid)
    {
      SizeT tileSetCount = tiledMap->getTileSetsCount();
      for (SizeT i = 0; i < tileSetCount; ++i)
      {
        const tmr::TileSet* tileSet = tiledMap->getTileSetAt(i);

        Int32 tileSetLastGid =
          tileSet->getFirstGid() + static_cast<Int32>(tileSet->getSize());

        if (gid >= tileSet->getFirstGid() && gid < tileSetLastGid)
          return tileSet;
      }

      throw RuntimeErrorException(
        String::Format("No tileset found for GID %d", gid)
      );
    }

    IsometricPositionTransformer getIsometricPositionTransformer(
      const tmr::TiledMap& tiledMap
    )
    {
      return IsometricPositionTransformer(
        static_cast<UInt32>(tiledMap.getTileWidth()),
        static_cast<UInt32>(tiledMap.getTileHeight())
      );
    }

    IsometricPositionTransformer getIsometricPositionTransformer(
      const rk::TiledMap& tiledMap
    )
    {
      const tmr::TiledMap* tmrTiledMap = tiledMap.getTmrTiledMap();
      return IsometricPositionTransformer(
        static_cast<UInt32>(tmrTiledMap->getTileWidth()),
        static_cast<UInt32>(tmrTiledMap->getTileHeight())
      );
    }
  }
}