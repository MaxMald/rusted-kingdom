#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h";

using sf::Vector2f;

namespace rk
{
  class SceneGraph;
  class TiledMap;
  class AssetManager;

  class TiledSceneBuilder
  {
  public:
    TiledSceneBuilder() = delete;

    static void buildFromTiledMap(
      SceneGraph& sceneGraph,
      const TiledMap& tiledMap,
      AssetManager& assetManager
    );

  private:

    static Vector2f computeTilePositionIsometric(
      const Int32& col,
      const Int32& row,
      const Int32& tileWidth,
      const Int32& tileHeight
    );
  };
}