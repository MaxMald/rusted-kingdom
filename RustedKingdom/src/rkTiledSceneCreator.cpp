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

#include "rkAssetManager.h"
#include "rkTiledMap.h"
#include "rkSceneGraph.h"
#include "rkTiledObjectSpriteDescriptorFactory.h"
#include "rkTileGameObjectBlueprint.h"
#include "rkSpriteComponent.h"
#include "rkSpriteComponentFactory.h"
#include "rkGameObject.h"
#include "rkLayerGameObjectBlueprint.h"

#include "rkIsometricPositionTransformer.h"
#include "rkIsometricPositionTransformerFactory.h"

using sf::Vector2f;
using sf::Vector2i;

namespace rk
{
  namespace tiledSceneCreator
  {
    static void createLayer(
      tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::Layer* tmrLayer
    );

    static void createGridDataLayer(
      tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::GridDataLayer* tmrLayer
    );

    static void createObjectGroupLayer(
      tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::ObjectGroupLayer* tmrLayer
    );

    static void createTile(
      tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      GameObject& parent,
      TileGameObjectBlueprint& tileGameObjectBlueprint,
      const sf::Vector2f& position,
      Int32 tileGid
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
      SpriteComponentFactory& spriteComponentFactory,
      SceneGraph& sceneGraph
    )
    {
      const SharedPtr<TiledMap> tiledMap = assetManager
        .getAssetGroup<TiledMap>()
        .get(tiledMapKey);

      tmr::TiledMap* tmrTiledMap = tiledMap->getTmrTiledMap();

      IsometricPositionTransformer isometricPosTransformer =
        isometricPositionTransformerFactory::create(*tmrTiledMap);

      SizeT layerCount = tmrTiledMap->getLayersCount();
      for (SizeT i = 0; i < layerCount; ++i)
      {
        createLayer(
          tmrTiledMap,
          sceneGraph,
          spriteComponentFactory,
          isometricPosTransformer,
          tmrTiledMap->getLayerAt(i)
        );
      }
    }

    static void createLayer(
      tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
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
          spriteComponentFactory,
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
      tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::GridDataLayer* tmrLayer
    )
    {
      GameObject* layerGameObject = createLayerGameObject(
        tmrLayer->getName(),
        sceneGraph
      );

      Int32 spriteWidth = tiledMap->getTileWidth();
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
            row * spriteHeight,
            column * spriteHeight
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
      tmr::TiledMap* tiledMap,
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

      sceneGraph.instantiateGameObject(
        tileGameObjectBlueprint,
        position,
        parent
      );
    }

    static void createObjectGroupLayer(
      tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      SpriteComponentFactory& spriteComponentFactory,
      IsometricPositionTransformer isometricPosTransformer,
      const tmr::ObjectGroupLayer* tmrLayer
    )
    {
      GameObject* layerGameObject = createLayerGameObject(
        tmrLayer->getName(),
        sceneGraph
      );

      TileGameObjectBlueprint tileGameObjectBlueprint(
        spriteComponentFactory
      );

      const tmr::ObjectGroup* tmrObjectGroup = tmrLayer->getObjectGroup();
      SizeT objectCount = tmrObjectGroup->getObjectSize();
      for (SizeT i = 0; i < objectCount; ++i)
      {
        const tmr::Object* tmrObject = tmrObjectGroup->getObjectAt(
          static_cast<UInt32>(i)
        );

        if (!tmrObject->isVisible())
          continue;

        Int32 gid = tmrObject->getGid();
        if (gid == 0)
          continue;

        Vector2f position = isometricPosTransformer.isometricToWorld(
          tmrObject->getX(),
          tmrObject->getY()
        );

        TiledObjectSpriteDescriptor tileSpriteDesc =
          tiledObjectSpriteDescriptorFactory::create(gid, tiledMap);

        tileSpriteDesc.setOrigin(0.5f, 1.0f);

        sceneGraph.instantiateGameObject(
          tileGameObjectBlueprint,
          position,
          *layerGameObject
        );
      }
    }

    GameObject* createLayerGameObject(const String& name, SceneGraph& sceneGraph)
    {
      LayerGameObjectBlueprint layerGameObjectBlueprint;
      return sceneGraph.instantiateGameObject(
        layerGameObjectBlueprint,
        name,
        Vector2f(0.0f, 0.0f),
        *sceneGraph.getRoot()
      );
    }
  }
}