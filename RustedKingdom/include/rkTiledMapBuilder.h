#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h";

using sf::Vector2f;

namespace tmr
{
  class TileMapLayer;
}

namespace rk
{
  class SceneGraph;
  class TiledMap;
  class AssetManager;
  class TileSetsManager;
  class TileDescription;

  class TiledSceneBuilder
  {
  public:
    TiledSceneBuilder() = delete;

    static void buildFromTiledMap(
      SceneGraph& sceneGraph,
      const TiledMap& tiledMap,
      const AssetManager& assetManager
    );

  private:

    static void buildFromTileLayer(
      SceneGraph& sceneGraph,
      const Int32& tileWidth,
      const Int32& tileHeight,
      const tmr::TileMapLayer& tileMapLayer,
      const TileSetsManager& tileSetsManager,
      const AssetManager& assetManager
    );

    static Vector2f computeTilePositionIsometric(
      const Int32& col,
      const Int32& row,
      const Int32& tileWidth,
      const Int32& tileHeight
    );

    static void createSpriteFromTileDescription(
      SceneGraph& sceneGraph,
      const Vector2f& position,
      const TileDescription& tileDescription,
      const AssetManager& assetManager
    );
  };
}