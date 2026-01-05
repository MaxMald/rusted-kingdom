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
#include "rkGameObjectUtilities.h"
#include "rkColliderComponent.h"
#include "rkIsometricLayerGameObject.h"
#include "rkTiledPropertiesHandler.h"
#include "rkTiledLayerGameObjectCreator.h"
#include "rkTiledClassApplierMapper.h"
#include "rkITiledClassApplier.h"

using sf::Vector2f;
using sf::Vector2i;

namespace rk
{
  namespace tiledSceneCreator
  {
    static void createLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      TiledClassApplierMapper& tiledClassApplierMapper,
      const tmr::Layer* tmrLayer
    );

    static void createGridDataLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      const tmr::GridDataLayer* tmrLayer
    );

    static void createObjectGroupLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      TiledClassApplierMapper& tiledClassApplierMapper,
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
  }
}

namespace rk
{
  namespace tiledSceneCreator
  {
    void create(
      const String& tiledMapKey,
      const AssetManager& assetManager,
      TiledClassApplierMapper& tiledClassApplierMapper,
      SceneGraph& sceneGraph
    )
    {
      const SharedPtr<TiledMap> tiledMap = assetManager
        .getAssetGroup<TiledMap>()
        .get(tiledMapKey);

      tmr::TiledMap* tmrTiledMap = tiledMap->getTmrTiledMap();

      SizeT layerCount = tmrTiledMap->getLayersCount();
      for (SizeT i = 0; i < layerCount; ++i)
      {
        createLayer(
          tmrTiledMap,
          sceneGraph,
          tiledClassApplierMapper,
          tmrTiledMap->getLayerAt(i)
        );
      }
    }

    static void createLayer(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      TiledClassApplierMapper& tiledClassApplierMapper,
      const tmr::Layer* tmrLayer
    )
    {
      tmr::layerType::Type layerType = tmrLayer->getType();
      if (layerType == tmr::layerType::Type::GridData)
      {
        createGridDataLayer(
          tiledMap,
          sceneGraph,
          static_cast<const tmr::GridDataLayer*>(tmrLayer)
        );
      }
      else if (layerType == tmr::layerType::Type::ObjectGroup)
      {
        createObjectGroupLayer(
          tiledMap,
          sceneGraph,
          tiledClassApplierMapper,
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
      const tmr::GridDataLayer* tmrLayer
    )
    {
      GameObject* layerGameObject = tiledLayerGameObjectCreator::create(
        tiledMap,
        tmrLayer,
        sceneGraph
      );

      Int32 spriteHeight = tiledMap->getTileHeight();
      Int32 width = tmrLayer->getWidth();
      Int32 height = tmrLayer->getHeight();
      TileGameObjectBlueprint tileGameObjectBlueprint;

      SharedPtr<IPositionTransformer> positionTransformer = 
        tiledMapUtilities::getPositionTransformer(*tiledMap);

      for (Int32 row = 0; row < height; ++row)
      {
        for (Int32 column = 0; column < width; ++column)
        {
          Vector2f position = positionTransformer->inverseTransform(
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
      TiledClassApplierMapper& tiledClassApplierMapper,
      const tmr::ObjectGroupLayer* tmrLayer
    )
    { 
      GameObject* layerGameObject = tiledLayerGameObjectCreator::create(
        tiledMap,
        tmrLayer,
        sceneGraph
      );

      String layerName = tmrLayer->getName();
      SharedPtr<IPositionTransformer> positionTransformer = 
        tiledMapUtilities::getPositionTransformer(*tiledMap);

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

        SharedPtr<ITiledClassApplier> classApplier = tiledClassApplierMapper
          .getClassApplier(tmrObject->getType());

        if (classApplier == nullptr)
          continue;

        GameObject* tileGameObject = new GameObject(tmrObject->getName());
        classApplier->apply(
          *tileGameObject,
          tmrObject,
          tiledMap
        );

        Vector2f position = positionTransformer->inverseTransform(
          tmrObject->getX(),
          tmrObject->getY()
        );
        tileGameObject->setPosition(position);

        Vector2f origin = tiledMapUtilities::getObjectOrigin(*tiledMap);
        gameObjectUtilities::setSpriteOrigin(*tileGameObject, origin.x, origin.y);

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
  }
}