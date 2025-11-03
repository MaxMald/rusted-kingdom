#include "rkTiledMapBuilder.h"
#include <SFML/Graphics/Texture.hpp>
#include <TMR/tmrMapLayer.h>
#include <TMR/tmrTileMapLayer.h>
#include "rkTiledMap.h"
#include "rkTileSetsManager.h"
#include "rkTileDescription.h"
#include "rkSpriteGameObject.h"
#include "rkGameObjectsFactory.h"

namespace rk
{
  void TiledSceneBuilder::buildFromTiledMap(
    GameObjectsFactory& gameObjectsFactory,
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
      if (mapLayer->getType() != tmr::mapLayerType::Type::TileLayer)
        continue;

      const tmr::TileMapLayer* tileMapLayer =
        static_cast<const tmr::TileMapLayer*>(mapLayer);

      buildFromTileLayer(
        gameObjectsFactory,
        tileWidth,
        tileHeight,
        *tileMapLayer,
        tiledMap.getTileSetsManager()
      );
    }
  }

  void TiledSceneBuilder::buildFromTileLayer(
    GameObjectsFactory& gameObjectsFactory,
    const Int32& tileWidth,
    const Int32& tileHeight,
    const tmr::TileMapLayer& tileMapLayer,
    const TileSetsManager& tileSetsManager
  )
  {
    Int32 numCols = tileMapLayer.getWidth();
    Int32 numRows = tileMapLayer.getHeight();

    for (Int32 row = 0; row < numRows; ++row)
    {
      for (Int32 col = 0; col < numCols; ++col)
      {
        const Int32 gid = tileMapLayer.getDataAt(col, row);

        if (gid == 0)
          continue;

        TileDescription tileDescription = tileSetsManager
          .getTileDescriptionByGid(gid);

        SpriteGameObject* tile = gameObjectsFactory.createSpriteGameObject(
          tileDescription.getTextureKey(),
          tileDescription.getTextureRect()
        );

        Vector2f tilePosition = computeTilePositionIsometric(
          col,
          row,
          tileWidth,
          tileHeight
        );

        tile->setPosition(tilePosition);
      }
    }
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

    const float x = (static_cast<float>(col) - static_cast<float>(row)) * halfW;
    const float y = (static_cast<float>(col) + static_cast<float>(row)) * halfH;

    return Vector2f(x, y);
  }
}