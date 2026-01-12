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
      SharedPtr<Pathfinder> pathfinder = MakeShared<Pathfinder>();
      initializeFromIsometricTiledMap(*pathfinder, tiledMap);
      return pathfinder;
    }

    void initializeFromIsometricTiledMap(
      Pathfinder& pathfinder,
      const TiledMap& tiledMap,
      UInt32 subdivisions
    )
    {
      if (subdivisions == 0)
        subdivisions = 1;

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

      UInt32 pathfinderWidth = width * subdivisions;
      UInt32 pathfinderHeight = height * subdivisions;
      UInt32 pathfinderXSpacing = tileHeight / subdivisions;
      UInt32 pathfinderYSpacing = tileHeight / subdivisions;

      pathfinder.init(
        pathfinderWidth,
        pathfinderHeight,
        pathfinderXSpacing,
        pathfinderYSpacing
      );

      // Transform node positions from isometric to world coordinates

      IsometricPositionTransformer isoTransformer(
        static_cast<UInt32>(tmrTiledMap->getTileWidth()),
        static_cast<UInt32>(tmrTiledMap->getTileHeight())
      );

      for (UInt32 column = 0; column < pathfinderWidth; ++column)
      {
        for (UInt32 row = 0; row < pathfinderHeight; ++row)
        {
          SharedPtr<Node> node = pathfinder.getNodeAt(column, row);
          Vector2f positionToTransform = node->getPosition();
          node->setPosition(isoTransformer.isometricToWorld(positionToTransform));
        }
      }

      // Update quad tree
      pathfinder.updateQuadTree();
    }
  }
}