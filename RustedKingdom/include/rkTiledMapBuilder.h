#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"

using sf::Vector2f;

namespace tmr
{
  class TileMapLayer;
  class ObjectGroupMapLayer;
  class Object;
}

namespace rk
{
  class SceneGraph;
  class TiledMap;
  class TiledObject;
  class TileSetsManager;
  class TileSetTile;
  class GameObjectBuilder;
  class GameObject;
  class SpriteComponentFactory;
  class RigidBodyComponentFactory;
  class IsometricPositionTransformer;

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
      GameObjectBuilder& gameObjectBuilder,
      SpriteComponentFactory& spriteComponentFactory,
      RigidBodyComponentFactory& rigidBodyComponentFactory,
      SceneGraph& sceneGraph,
      const TiledMap& tiledMap
    );

  private:

    /**
     * @brief Processes a single tile layer and add its tiles to the scene
     * graph.
     */
    static void buildFromTileLayer(
      GameObjectBuilder& gameObjectBuilder,
      SpriteComponentFactory& spriteComponentFactory,
      SceneGraph& sceneGraph,
      const Int32& tileWidth,
      const Int32& tileHeight,
      const tmr::TileMapLayer& tileMapLayer,
      const TileSetsManager& tileSetsManager,
      const IsometricPositionTransformer& isometricPositionTransformer
    );

    static void buildFromObjectGroupLayer(
      GameObjectBuilder& gameObjectBuilder,
      SpriteComponentFactory& spriteComponentFactory,
      RigidBodyComponentFactory& rigidBodyComponentFactory,
      SceneGraph& sceneGraph,
      const tmr::ObjectGroupMapLayer& objectGroupLayer,
      const TileSetsManager& tileSetsManager,
      const IsometricPositionTransformer& isometricPositionTransformer
    );

    static const TiledObject& getColliderObject(const TileSetTile& tileSetTile);
    static bool hasCollider(const TileSetTile& tileSetTile);
    static void addCollider(
      GameObject& gameObject,
      const TiledObject& colliderObject,
      RigidBodyComponentFactory& rigidBodyComponentFactory
    );
  };
}