#pragma once

#include "rkPrerequisites.h"

namespace tmr
{
  class TiledMap;
}

namespace rk
{
  class IsometricPositionTransformer;
  class TiledMap;

  namespace isometricPositionTransformerFactory
  {
    IsometricPositionTransformer create(const tmr::TiledMap& tiledMap);
    IsometricPositionTransformer create(const rk::TiledMap& tiledMap);
  }
}