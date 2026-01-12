#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class Pathfinder;
  class TiledMap;

  namespace pathfinderFactory
  {
    SharedPtr<Pathfinder> createFromIsometricTiledMap(
      const TiledMap& tiledMap
    );

    void initializeFromIsometricTiledMap(
      Pathfinder& pathfinder,
      const TiledMap& tiledMap,
      UInt32 subdivisions = 1
    );
  }
}