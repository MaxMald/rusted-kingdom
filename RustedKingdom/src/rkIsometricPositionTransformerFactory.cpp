#include "rkIsometricPositionTransformerFactory.h"

#include <TMR/tmrTiledMap.h>

#include "rkIsometricPositionTransformer.h"
#include "rkTiledMap.h"

namespace rk
{
  namespace isometricPositionTransformerFactory
  {
    IsometricPositionTransformer create(const tmr::TiledMap& tiledMap)
    {
      return IsometricPositionTransformer(
        static_cast<UInt32>(tiledMap.getTileWidth()),
        static_cast<UInt32>(tiledMap.getTileHeight())
      );
    }

    IsometricPositionTransformer create(const rk::TiledMap& tiledMap)
    {
      const tmr::TiledMap* tmrTiledMap = tiledMap.getTmrTiledMap();
      return IsometricPositionTransformer(
        static_cast<UInt32>(tmrTiledMap->getTileWidth()),
        static_cast<UInt32>(tmrTiledMap->getTileHeight())
      );
    }
  }
}