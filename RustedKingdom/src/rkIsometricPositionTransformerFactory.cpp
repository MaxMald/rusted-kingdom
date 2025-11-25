#include "rkIsometricPositionTransformerFactory.h"

#include <TMR/tmrTiledMap.h>

#include "rkIsometricPositionTransformer.h"

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
  }
}