#include "rkPathfinderFactory.h"

#include <TMR/tmrTiledMap.h>

#include "rkPathfinder.h"
#include "rkTiledMap.h"
#include "rkCollider.h"
#include "rkIsometricPositionTransformer.h"

namespace rk
{
  namespace pathfinderFactory
  {
    SharedPtr<Pathfinder> createFromIsometricTiledMap(
      const TiledMap& tiledMap
    )
    {
      const tmr::TiledMap* tmrTiledMap = tiledMap.getTmrTiledMap();

      if (tmrTiledMap->getOrientation() != tmr::orientation::Type::Isometric)
      {
        throw RuntimeErrorException(
          "pathfinderFactory::createFromIsometricTiledMap: "
          "Unsupported map orientation."
        );
      }

      UInt32 width = static_cast<UInt32>(tmrTiledMap->getWidth());
      UInt32 height = static_cast<UInt32>(tmrTiledMap->getHeight());
      UInt32 tileHeight = static_cast<UInt32>(tmrTiledMap->getTileHeight());

      return MakeShared<Pathfinder>(
        width,
        height,
        tileHeight,
        tileHeight
      );
    }
  }
}