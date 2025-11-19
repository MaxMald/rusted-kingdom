#include "rkTiledSceneFactory.h"

#include <SFML/Graphics/Texture.hpp>
#include <TMR/tmrMapLayer.h>
#include <TMR/tmrTileMapLayer.h>
#include <TMR/tmrTileSetTile.h>
#include <TMR/tmrObjectGroupMapLayer.h>
#include <TMR/tmrObjectGroup.h>
#include <TMR/tmrObject.h>

#include "rkSceneGraph.h"
#include "rkPhysicWorld.h"
#include "rkTiledMap.h"
#include "rkTileSetsManager.h"
#include "rkTileDescription.h"
#include "rkTileSetTile.h"
#include "rkLayerGameObject.h"
#include "rkGameObjectBuilder.h"
#include "rkSpriteComponentFactory.h"
#include "rkSpriteComponent.h"
#include "rkRigidBodyComponentFactory.h"
#include "rkRigidBodyComponent.h"
#include "rkColliderComponentFactory.h"
#include "rkCircleColliderComponent.h"

namespace rk
{
  TiledSceneFactory::TiledSceneFactory(
    GameObjectBuilder& gameObjectBuilder,
    SpriteComponentFactory& spriteComponentFactory,
    RigidBodyComponentFactory& rigidBodyComponentFactory,
    ColliderComponentFactory& colliderComponentFactory,
    SceneGraph& sceneGraph,
    PhysicWorld& physicWorld
  ) :
    m_gameObjectBuilder(gameObjectBuilder),
    m_spriteComponentFactory(spriteComponentFactory),
    m_rigidBodyComponentFactory(rigidBodyComponentFactory),
    m_colliderComponentFactory(colliderComponentFactory),
    m_sceneGraph(sceneGraph),
    m_physicWorld(physicWorld)
  {
  }

  TiledSceneFactory::~TiledSceneFactory()
  {
  }

  void TiledSceneFactory::create(const TiledMap& tiledMap)
  {
    if (tiledMap.getOrientation() != tmr::orientation::Type::Isometric)
    {
      throw RuntimeErrorException(
        "TiledSceneBuilder::buildFromTiledMap: Unsupported map orientation."
      );
    }

    const SizeT numLayers = tiledMap.getLayersCount();
    const Vector2i tileSize = Vector2i(
      tiledMap.getTileWidth(),
      tiledMap.getTileHeight()
    );

    for (SizeT layerIndex = 0; layerIndex < numLayers; ++layerIndex)
    {
      const tmr::MapLayer* mapLayer = tiledMap.getLayerAt(layerIndex);

      if (mapLayer->getType() == tmr::mapLayerType::Type::TileLayer)
      {
        const tmr::TileMapLayer* tileMapLayer =
          static_cast<const tmr::TileMapLayer*>(mapLayer);

        buildFromTileLayer(
          tileSize,
          *tileMapLayer,
          tiledMap.getTileSetsManager(),
          tiledMap.getIsometricPositionTransformer()
        );
      }

      else if (mapLayer->getType() == tmr::mapLayerType::Type::ObjectGroup)
      {
        const tmr::ObjectGroupMapLayer* objectGroupLayer =
          static_cast<const tmr::ObjectGroupMapLayer*>(mapLayer);

        buildFromObjectGroupLayer(
          *objectGroupLayer,
          tiledMap.getTileSetsManager(),
          tiledMap.getIsometricPositionTransformer()
        );
      }
    }
  }

  const TiledObject& TiledSceneFactory::GetColliderObject(
    const TileSetTile& tileSetTile
  )
  {
    const TiledObjectGroup& objectGroup = tileSetTile.getTiledObjectGroup();
    for (const TiledObject& tiledObject : objectGroup.getObjects())
    {
      if (tiledObject.getType() == "collider")
        return tiledObject;
    }

    throw RuntimeErrorException(
      "TiledSceneBuilder::getColliderObject: No collider object found in TileSetTile."
    );
  }

  bool TiledSceneFactory::HasCollider(const TileSetTile& tmrTileSetTile)
  {
    const TiledObjectGroup& objectGroup = tmrTileSetTile.getTiledObjectGroup();
    if (objectGroup.getSize() == 0)
      return false;

    for (const TiledObject& tiledObject : objectGroup.getObjects())
    {
      if (tiledObject.getType() == "collider")
        return true;
    }

    return false;
  }

  void TiledSceneFactory::buildFromTileLayer(
    const Vector2i& tileSize,
    const tmr::TileMapLayer& tileMapLayer,
    const TileSetsManager& tileSetsManager,
    const IsometricPositionTransformer& isometricPositionTransformer
  )
  {
    Int32 numCols = tileMapLayer.getWidth();
    Int32 numRows = tileMapLayer.getHeight();
    float halfTileWidth = static_cast<float>(tileSize.x) * 0.5f;

    LayerGameObject* layerGameObject = new LayerGameObject(
      tileMapLayer.getName()
    );
    m_sceneGraph.getRoot()->addChild(UniquePtr<LayerGameObject>(layerGameObject));

    for (Int32 row = 0; row < numRows; ++row)
    {
      for (Int32 col = 0; col < numCols; ++col)
      {
        const Int32 gid = tileMapLayer.getDataAt(col, row);

        if (gid == 0)
          continue;

        TileDescription tileDescription = tileSetsManager
          .getTileDescriptionByGid(gid);

        Vector2f tilePosition = isometricPositionTransformer.isometricToWorld(
          static_cast<float>(col) * tileSize.y,
          static_cast<float>(row) * tileSize.y
        );

        GameObject* tileGameObject = m_gameObjectBuilder
          .createGameObject()
          .withPosition(tilePosition)
          .buildWithParent(*layerGameObject);

        UniquePtr<SpriteComponent> spriteComponent =
          m_spriteComponentFactory.createSpriteComponent(
            *tileGameObject,
            tileDescription.getTextureKey(),
            tileDescription.getTextureRect()
          );

        spriteComponent->setOrigin(
          Vector2f(halfTileWidth, 0.0f)
        );

        tileGameObject->addComponent(std::move(spriteComponent));
      }
    }
  }

  void TiledSceneFactory::buildFromObjectGroupLayer(
    const tmr::ObjectGroupMapLayer& objectGroupLayer,
    const TileSetsManager& tileSetsManager,
    const IsometricPositionTransformer& isometricPositionTransformer
  )
  {
    String objectGroupName = objectGroupLayer.getName();

    LayerGameObject* layerGameObject = new LayerGameObject(
      objectGroupName.c_str()
    );

    m_physicWorld.createCollidersGroup(
      objectGroupName
    );

    m_sceneGraph.getRoot()->addChild(UniquePtr<LayerGameObject>(layerGameObject));

    SizeT objectsSize = objectGroupLayer.getObjectSize();
    for (SizeT objIndex = 0; objIndex < objectsSize; ++objIndex)
    {
      const tmr::Object* object = objectGroupLayer.getObjectAt(objIndex);

      if (!object->isVisible())
        continue;

      TileDescription tileDescription = tileSetsManager
        .getTileDescriptionByGid(object->getGid());

      Vector2f tilePosition = isometricPositionTransformer.isometricToWorld(
        object->getX(),
        object->getY()
      );

      GameObject* objectGameObject = m_gameObjectBuilder
        .createGameObject()
        .withPosition(tilePosition)
        .buildWithParent(*layerGameObject);

      UniquePtr<SpriteComponent> spriteComponent =
        m_spriteComponentFactory.createSpriteComponent(
          *objectGameObject,
          tileDescription.getTextureKey(),
          tileDescription.getTextureRect()
        );

      Vector2f spriteOrigin = Vector2f(
        static_cast<float>(tileDescription.getTextureRect().size.x) * 0.5f,
        static_cast<float>(tileDescription.getTextureRect().size.y)
      );

      spriteComponent->setOrigin(spriteOrigin);

      objectGameObject->addComponent(std::move(spriteComponent));

      const TileSetTile& tileSetTile = tileSetsManager.getTileSetTileByGid(
        object->getGid()
      );

      if (!HasCollider(tileSetTile))
        continue;

      const TiledObject& colliderObject = GetColliderObject(tileSetTile);
      addCollider(
        *objectGameObject,
        colliderObject,
        objectGroupName,
        spriteOrigin
      );
    }
  }

  void TiledSceneFactory::addCollider(
    GameObject& gameObject,
    const TiledObject& colliderObject,
    const String& colliderGroupKey,
    const Vector2f& spriteOrigin
  )
  {
    UniquePtr<RigidBodyComponent> rigidBody = m_rigidBodyComponentFactory
      .create(
        gameObject,
        rigidBodyType::Static
      );
    gameObject.addComponent(std::move(rigidBody));

    float circleColliderRadius = colliderObject.getSize().x * 0.5f;
    Vector2f colliderLocalPosition = colliderObject.getPosition();
    Vector2f position = colliderLocalPosition - spriteOrigin;
    position += Vector2f(circleColliderRadius, circleColliderRadius);

    UniquePtr<CircleColliderComponent> collider = m_colliderComponentFactory
      .createCircle(
        gameObject,
        position,
        circleColliderRadius,
        colliderGroupKey
     );
    collider->setDebug(true);

    gameObject.addComponent(std::move(collider));
  }
}