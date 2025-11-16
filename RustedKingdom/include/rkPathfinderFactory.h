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
  }
}