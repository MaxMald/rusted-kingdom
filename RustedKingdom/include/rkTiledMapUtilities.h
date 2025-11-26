#pragma once

#include "rkPrerequisites.h"

namespace tmr
{
  class TiledMap;
  class TileSet;
}

namespace rk
{
  class IsometricPositionTransformer;
  class TiledMap;

  namespace tiledMapUtilities
  {
    const tmr::TileSet* getTileSetWithGid(
      const tmr::TiledMap* tiledMap,
      Int32 gid
    );

    IsometricPositionTransformer getIsometricPositionTransformer(
      const tmr::TiledMap& tiledMap
    );

    IsometricPositionTransformer getIsometricPositionTransformer(
      const rk::TiledMap& tiledMap
    );
  }
}