#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h";

using sf::Vector2f;

namespace tmr
{
  class TileMapLayer;
  class ObjectGroupMapLayer;
}

namespace rk
{
  class SceneGraph;
  class TiledMap;
  class TileSetsManager;
  class GameObjectsFactory;

  /**
   * @brief Helper class to construct a SceneGraph from a Tiled map.
   */
  class TiledSceneBuilder
  {
  public:
    TiledSceneBuilder() = delete;

    /**
     * @brief Builds a scene graph from the provided Tiled map.
     *
     * @param gameObjectsFactory Factory used to create and register game
     * objects into the scene graph.
     * @param tiledMap Reference to the Tiled map to build the scene from.
     */
    static void buildFromTiledMap(
      GameObjectsFactory& gameObjectsFactory,
      SceneGraph& sceneGraph,
      const TiledMap& tiledMap
    );

  private:

    /**
     * @brief Processes a single tile layer and add its tiles to the scene
     * graph.
     */
    static void buildFromTileLayer(
      GameObjectsFactory& gameObjectsFactory,
      SceneGraph& sceneGraph,
      const Int32& tileWidth,
      const Int32& tileHeight,
      const tmr::TileMapLayer& tileMapLayer,
      const TileSetsManager& tileSetsManager
    );

    /**
     * @brief Processes a single object group layer and add its objects to the
     * scene graph.
     */
    static void buildFromObjectGroupLayer(
      GameObjectsFactory& gameObjectsFactory,
      SceneGraph& sceneGraph,
      const Int32& tileWidth,
      const Int32& tileHeight,
      const tmr::ObjectGroupMapLayer& objectGroupLayer,
      const TileSetsManager& tileSetsManager
    );

    static Vector2f computeIsometricToWorldPosition(
      const float& x,
      const float& y,
      const Int32& halfWidth,
      const Int32& halfHeight
    );

    /**
     * @brief Compute the world position for an isometric tile.
     */
    static Vector2f computeTilePositionIsometric(
      const Int32& col,
      const Int32& row,
      const Int32& tileWidth,
      const Int32& tileHeight
    );
  };
}