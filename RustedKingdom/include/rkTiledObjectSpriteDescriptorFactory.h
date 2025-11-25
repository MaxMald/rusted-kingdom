#pragma once

#include "rkPrerequisites.h"
#include "rkTiledObjectSpriteDescriptor.h"

namespace tmr
{
  class TiledMap;
}

namespace rk
{
  namespace tiledObjectSpriteDescriptorFactory
  {
    TiledObjectSpriteDescriptor create(
      Int32 gid,
      tmr::TiledMap* tiledMap
    );
  }
}