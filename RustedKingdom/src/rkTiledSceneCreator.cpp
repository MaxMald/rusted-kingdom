#include "rkTiledSceneCreator.h"

#include <SFML/System/Vector2.hpp>

#include <TMR/tmrTiledMap.h>
#include <TMR/tmrGridDataLayer.h>
#include <TMR/tmrObjectGroupLayer.h>
#include <TMR/tmrObjectGroup.h>
#include <TMR/tmrImageCollectionTileSet.h>
#include <TMR/tmrSpriteSheetTileSet.h>
#include <TMR/tmrImage.h>
#include <TMR/tmrTileSetTile.h>
#include <TMR/tmrObject.h>
#include <TMR/tmrTileReferenceObject.h>
#include <TMR/tmrProperties.h>

#include "rkAssetManager.h"
#include "rkTiledMap.h"
#include "rkTiledMapUtilities.h"
#include "rkSceneGraph.h"
#include "rkTiledObjectSpriteDescriptorFactory.h"
#include "rkTileGameObjectBlueprint.h"
#include "rkSpriteComponent.h"
#include "rkSpriteComponentFactory.h"
#include "rkGameObject.h"
#include "rkIsometricPositionTransformer.h"
#include "rkTiledObjectCreator.h"
#include "rkGameObjectUtilities.h"
#include "rkColliderComponent.h"
#include "rkIsometricLayerGameObject.h"
#include "rkTiledPropertiesHandler.h"
#include "rkColliderComponent.h"

using sf::Vector2f;
using sf::Vector2i;

namespace rk
{
  namespace tiledSceneCreator
  {
    static void createLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      TiledObjectCreator& tiledObjectCreator,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::Layer* tmrLayer
    );

    static void createGridDataLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::GridDataLayer* tmrLayer
    );

    static void createObjectGroupLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      TiledObjectCreator& tiledObjectCreator,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::ObjectGroupLayer* tmrLayer
    );

    static void createTile(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      GameObject& parent,
      TileGameObjectBlueprint& tileGameObjectBlueprint,
      const sf::Vector2f& position,
      Int32 tileGid
    );

    static void fixColliderCenterBaseOnOrigin(GameObject& gameObject);
    static void activeDebugCollider(GameObject& gameObject);

    static GameObject* createLayerGameObject(
      const String& name,
      const tmr::Properties* layerProperties,
      SceneGraph& sceneGraph
    );
  }
}

namespace rk
{
  namespace tiledSceneCreator
  {
    void create(
      const String& tiledMapKey,
      const AssetManager& assetManager,
      TiledObjectCreator& tiledObjectCreator,
      SpriteComponentFactory& spriteComponentFactory,
      SceneGraph& sceneGraph
    )
    {
      const SharedPtr<TiledMap> tiledMap = assetManager
        .getAssetGroup<TiledMap>()
        .get(tiledMapKey);

      tmr::TiledMap* tmrTiledMap = tiledMap->getTmrTiledMap();

      IsometricPositionTransformer isometricPosTransformer =
        tiledMapUtilities::getIsometricPositionTransformer(*tmrTiledMap);

      SizeT layerCount = tmrTiledMap->getLayersCount();
      for (SizeT i = 0; i < layerCount; ++i)
      {
        createLayer(
          tmrTiledMap,
          sceneGraph,
          spriteComponentFactory,
          tiledObjectCreator,
          isometricPosTransformer,
          tmrTiledMap->getLayerAt(i)
        );
      }
    }

    static void createLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      TiledObjectCreator& tiledObjectCreator,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::Layer* tmrLayer
    )
    {
      tmr::layerType::Type layerType = tmrLayer->getType();
      if (layerType == tmr::layerType::Type::GridData)
      {
        createGridDataLayer(
          tiledMap,
          sceneGraph,
          spriteComponentFactory,
          isometricPosTransformer,
          static_cast<const tmr::GridDataLayer*>(tmrLayer)
        );
      }
      else if (layerType == tmr::layerType::Type::ObjectGroup)
      {
        createObjectGroupLayer(
          tiledMap,
          sceneGraph,
          tiledObjectCreator,
          isometricPosTransformer,
          static_cast<const tmr::ObjectGroupLayer*>(tmrLayer)
        );
      }
      else
      {
        throw RuntimeErrorException(
          String::Format(
            "Unsupported Tiled layer type: %d",
            static_cast<Int32>(layerType)
          )
        );
      }
    }

    static void createGridDataLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::GridDataLayer* tmrLayer
    )
    {
      GameObject* layerGameObject = createLayerGameObject(
        tmrLayer->getName(),
        tmrLayer->getProperties(),
        sceneGraph
      );

      Int32 spriteHeight = tiledMap->getTileHeight();
      Int32 width = tmrLayer->getWidth();
      Int32 height = tmrLayer->getHeight();
      TileGameObjectBlueprint tileGameObjectBlueprint(
        spriteComponentFactory
      );

      for (Int32 row = 0; row < height; ++row)
      {
        for (Int32 column = 0; column < width; ++column)
        {
          Vector2f position = isometricPosTransformer.isometricToWorld(
            static_cast<float>(column * spriteHeight),
            static_cast<float>(row * spriteHeight)
          );

          createTile(
            tiledMap,
            sceneGraph,
            *layerGameObject,
            tileGameObjectBlueprint,
            position,
            tmrLayer->getDataAt(column, row)
          );
        }
      }
    }

    static void createTile(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      GameObject& parent,
      TileGameObjectBlueprint& tileGameObjectBlueprint,
      const Vector2f& position,
      Int32 tileGid
    )
    {
      if (tileGid == 0)
        return;

      TiledObjectSpriteDescriptor tileSpriteDesc =
        tiledObjectSpriteDescriptorFactory::create(tileGid, tiledMap);

      tileSpriteDesc.setOrigin(0.5f, 0.0f);

      tileGameObjectBlueprint.setDescription(tileSpriteDesc);

      sceneGraph.instantiateGameObject(
        tileGameObjectBlueprint,
        position,
        parent
      );
    }

    static void createObjectGroupLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      TiledObjectCreator& tiledObjectCreator,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::ObjectGroupLayer* tmrLayer
    )
    {
      String layerName = tmrLayer->getName();
      GameObject* layerGameObject = createLayerGameObject(
        layerName,
        tmrLayer->getProperties(),
        sceneGraph
      );

      tiledObjectCreator.setColliderGroupKey(layerName);

      const tmr::ObjectGroup* tmrObjectGroup = tmrLayer->getObjectGroup();
      SizeT objectCount = tmrObjectGroup->getObjectSize();
      for (SizeT i = 0; i < objectCount; ++i)
      {
        const tmr::Object* tmrObject = tmrObjectGroup->getObjectAt(
          static_cast<UInt32>(i)
        );

        if (!tmrObject->isVisible())
          continue;

        if (tmrObject->getObjectType() != tmr::objectType::Type::TileReference)
          continue;

        GameObject* tileGameObject = tiledObjectCreator.create(
          tiledMap,
          tmrObject
        );

        Vector2f position = isometricPosTransformer.isometricToWorld(
          tmrObject->getX(),
          tmrObject->getY()
        );

        tileGameObject->setPosition(position);
        gameObjectUtilities::setSpriteOrigin(*tileGameObject, 0.5f, 1.0f);
        fixColliderCenterBaseOnOrigin(*tileGameObject);
        activeDebugCollider(*tileGameObject);

        sceneGraph.registerGameObject(
          UniquePtr<GameObject>(tileGameObject),
          *layerGameObject
        );
      }
    }

    static void fixColliderCenterBaseOnOrigin(GameObject& gameObject)
    {
      if (!gameObject.hasComponent<ColliderComponent>() ||
          !gameObject.hasComponent<SpriteComponent>())
      {
        return;
      }

      ColliderComponent* colliderComponent = gameObject
        .getComponent<ColliderComponent>();

      SpriteComponent* spriteComponent = gameObject
        .getComponent<SpriteComponent>();

      colliderComponent->setCenter(
        colliderComponent->getCenter() - spriteComponent->getOrigin()
      );
    }

    static void activeDebugCollider(GameObject& gameObject)
    {
      if (!gameObject.hasComponent<ColliderComponent>())
        return;

      ColliderComponent* colliderComponent = gameObject
        .getComponent<ColliderComponent>();

      colliderComponent->setDebug(true);
    }

    static GameObject* createLayerGameObject(
      const String& name,
      const tmr::Properties* layerProperties,
      SceneGraph& sceneGraph
    )
    {
      IsometricLayerGameObject* layerGameObject
        = new IsometricLayerGameObject(name);

      TiledPropertiesHandler propertiesHandler(layerProperties);
      
      bool isStatic = false;
      propertiesHandler.tryGetBool("isStatic", isStatic);
      layerGameObject->setStaticLayer(isStatic);

      sceneGraph.registerGameObject(
        UniquePtr<GameObject>(layerGameObject)
      );

      return layerGameObject;
    }
  }
}