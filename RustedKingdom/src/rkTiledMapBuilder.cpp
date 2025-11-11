#include "rkTiledMapBuilder.h"

#include <SFML/Graphics/Texture.hpp>
#include <TMR/tmrMapLayer.h>
#include <TMR/tmrTileMapLayer.h>
#include <TMR/tmrObjectGroupMapLayer.h>
#include <TMR/tmrObject.h>

#include "rkSceneGraph.h"
#include "rkTiledMap.h"
#include "rkTileSetsManager.h"
#include "rkTileDescription.h"
#include "rkLayerGameObject.h"
#include "rkGameObjectBuilder.h"

namespace rk
{
  void TiledSceneBuilder::buildFromTiledMap(
    GameObjectBuilder& gameObjectBuilder,
    SceneGraph& sceneGraph,
    const TiledMap& tiledMap
  )
  {
    if (tiledMap.getOrientation() != tmr::orientation::Type::Isometric)
    {
      throw RuntimeErrorException(
        "TiledSceneBuilder::buildFromTiledMap: Unsupported map orientation."
      );
    }

    const SizeT numLayers = tiledMap.getLayersCount();
    const Int32 tileWidth = tiledMap.getTileWidth();
    const Int32 tileHeight = tiledMap.getTileHeight();

    for (SizeT layerIndex = 0; layerIndex < numLayers; ++layerIndex)
    {
      const tmr::MapLayer* mapLayer = tiledMap.getLayerAt(layerIndex);

      if (mapLayer->getType() == tmr::mapLayerType::Type::TileLayer)
      {
        const tmr::TileMapLayer* tileMapLayer =
          static_cast<const tmr::TileMapLayer*>(mapLayer);

        buildFromTileLayer(
          gameObjectBuilder,
          sceneGraph,
          tileWidth,
          tileHeight,
          *tileMapLayer,
          tiledMap.getTileSetsManager()
        );
      }

      else if (mapLayer->getType() == tmr::mapLayerType::Type::ObjectGroup)
      {
        const tmr::ObjectGroupMapLayer* objectGroupLayer =
          static_cast<const tmr::ObjectGroupMapLayer*>(mapLayer);

        buildFromObjectGroupLayer(
          gameObjectBuilder,
          sceneGraph,
          tileWidth,
          tileHeight,
          *objectGroupLayer,
          tiledMap.getTileSetsManager()
        );
      }
    }
  }

  void TiledSceneBuilder::buildFromTileLayer(
    GameObjectBuilder& gameObjectBuilder,
    SceneGraph& sceneGraph,
    const Int32& tileWidth,
    const Int32& tileHeight,
    const tmr::TileMapLayer& tileMapLayer,
    const TileSetsManager& tileSetsManager
  )
  {
    Int32 numCols = tileMapLayer.getWidth();
    Int32 numRows = tileMapLayer.getHeight();

    LayerGameObject* layerGameObject = new LayerGameObject(
      tileMapLayer.getName()
    );
    sceneGraph.getRoot()->addChild(UniquePtr<LayerGameObject>(layerGameObject));

    for (Int32 row = 0; row < numRows; ++row)
    {
      for (Int32 col = 0; col < numCols; ++col)
      {
        const Int32 gid = tileMapLayer.getDataAt(col, row);

        if (gid == 0)
          continue;

        TileDescription tileDescription = tileSetsManager
          .getTileDescriptionByGid(gid);

        Vector2f tilePosition = computeTilePositionIsometric(
          col,
          row,
          tileWidth,
          tileHeight
        );

        gameObjectBuilder.createGameObject()
          .position(tilePosition)
          .withSpriteComponent(
            tileDescription.getTextureKey(),
            tileDescription.getTextureRect()
          )
          .buildWithParent(*layerGameObject);
      }
    }
  }

  void TiledSceneBuilder::buildFromObjectGroupLayer(
    GameObjectBuilder& gameObjectBuilder,
    SceneGraph& sceneGraph,
    const Int32& tileWidth,
    const Int32& tileHeight,
    const tmr::ObjectGroupMapLayer& objectGroupLayer,
    const TileSetsManager& tileSetsManager
  )
  {
    const Int32 halfTileWidth = tileWidth / 2;
    const Int32 halfTileHeight = tileHeight / 2;

    LayerGameObject* layerGameObject = new LayerGameObject(
      objectGroupLayer.getName()
    );
    sceneGraph.getRoot()->addChild(UniquePtr<LayerGameObject>(layerGameObject));

    SizeT objectsSize = objectGroupLayer.getObjectSize();
    for (SizeT objIndex = 0; objIndex < objectsSize; ++objIndex)
    {
      const tmr::Object* object = objectGroupLayer.getObjectAt(objIndex);

      if (!object->isVisible())
        continue;

      TileDescription tileDescription = tileSetsManager
        .getTileDescriptionByGid(object->getGid());

      Vector2f tilePosition = computeIsometricToWorldPosition(
        object->getX(),
        object->getY(),
        halfTileWidth,
        halfTileHeight
      );
      gameObjectBuilder.createGameObject()
        .position(tilePosition)
        .withSpriteComponent(
          tileDescription.getTextureKey(),
          tileDescription.getTextureRect()
        )
        .buildWithParent(*layerGameObject);
    }
  }

  Vector2f TiledSceneBuilder::computeIsometricToWorldPosition(
    const float& x,
    const float& y,
    const Int32& halfWidth,
    const Int32& halfHeight
  )
  {
    float wX = ((static_cast<float>(x)) - static_cast<float>(y)) + halfWidth;
    float wY = ((static_cast<float>(x)) + static_cast<float>(y)) * halfHeight / halfWidth;
    return Vector2f(wX, wY);
  }

  Vector2f TiledSceneBuilder::computeTilePositionIsometric(
    const Int32& col,
    const Int32& row,
    const Int32& tileWidth,
    const Int32& tileHeight
  )
  {
    const float halfW = static_cast<float>(tileWidth) * 0.5f;
    const float halfH = static_cast<float>(tileHeight) * 0.5f;

    float x = ((static_cast<float>(col) - static_cast<float>(row)) * halfW);
    float y = (static_cast<float>(col) + static_cast<float>(row)) * halfH;

    return Vector2f(x, y);
  }
}