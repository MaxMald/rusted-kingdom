#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

using sf::Vector2f;
using sf::Vector2i;

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
  class ColliderComponentFactory;
  class IsometricPositionTransformer;

  class TiledSceneFactory : public NonCopyable
  {
  public:
    TiledSceneFactory(
      GameObjectBuilder&,
      SpriteComponentFactory&,
      RigidBodyComponentFactory&,
      ColliderComponentFactory&,
      SceneGraph&
    );
    ~TiledSceneFactory();

    void create(const TiledMap& tiledMap);

  private:
    GameObjectBuilder& m_gameObjectBuilder;
    SpriteComponentFactory& m_spriteComponentFactory;
    RigidBodyComponentFactory& m_rigidBodyComponentFactory;
    ColliderComponentFactory& m_colliderComponentFactory;
    SceneGraph& sceneGraph;

    static const TiledObject& GetColliderObject(const TileSetTile& tileSetTile);
    static bool HasCollider(const TileSetTile& tileSetTile);

    void buildFromTileLayer(
      const Vector2i& tileSize,
      const tmr::TileMapLayer& tileMapLayer,
      const TileSetsManager& tileSetsManager,
      const IsometricPositionTransformer& isometricPositionTransformer
    );

    void buildFromObjectGroupLayer(
      const tmr::ObjectGroupMapLayer& objectGroupLayer,
      const TileSetsManager& tileSetsManager,
      const IsometricPositionTransformer& isometricPositionTransformer
    );

    void addCollider(
      GameObject&,
      const TiledObject&,
      const Vector2f& spriteOrigin
    );
  };
}