#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"

using sf::Vector2f;

namespace tmr
{
  class TiledMap;
  class TileSet;
}

namespace rk
{
  class IPositionTransformer;
  class TiledMap;

  namespace tiledMapUtilities
  {
    const tmr::TileSet* getTileSetWithGid(
      const tmr::TiledMap* tiledMap,
      Int32 gid
    );

    SharedPtr<IPositionTransformer> getPositionTransformer(
      const tmr::TiledMap& tiledMap
    );

    SharedPtr<IPositionTransformer> getPositionTransformer(
      const rk::TiledMap& tiledMap
    );

    Vector2f getObjectOrigin(
      const tmr::TiledMap& tiledMap
    );
  }
}