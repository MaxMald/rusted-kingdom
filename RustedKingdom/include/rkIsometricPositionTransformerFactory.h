#pragma once

#include "rkPrerequisites.h"

namespace tmr
{
  class TiledMap;
}

namespace rk
{
  class IsometricPositionTransformer;

  namespace isometricPositionTransformerFactory
  {
    IsometricPositionTransformer create(const tmr::TiledMap& tiledMap);
  }
}