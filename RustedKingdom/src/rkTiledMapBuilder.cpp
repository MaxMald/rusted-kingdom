#include "rkTiledMapBuilder.h"
#include <SFML/Graphics/Texture.hpp>
#include <TMR/tmrMapLayer.h>
#include <TMR/tmrTileMapLayer.h>
#include "rkTiledMap.h"
#include "rkTileSetsManager.h"
#include "rkTileDescription.h"
#include "rkAssetManager.h"
#include "rkSpriteGameObject.h"
#include "rkSceneGraph.h"

namespace rk
{
  void TiledSceneBuilder::buildFromTiledMap(
    SceneGraph& sceneGraph,
    const TiledMap& tiledMap,
    const AssetManager& assetManager
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
        sceneGraph,
        tileWidth,
        tileHeight,
        *tileMapLayer,
        tiledMap.getTileSetsManager(),
        assetManager
      );
    }
  }

  void TiledSceneBuilder::buildFromTileLayer(
    SceneGraph& sceneGraph,
    const Int32& tileWidth,
    const Int32& tileHeight,
    const tmr::TileMapLayer& tileMapLayer,
    const TileSetsManager& tileSetsManager,
    const AssetManager& assetManager
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

        Vector2f tilePosition = computeTilePositionIsometric(
          col,
          row,
          tileWidth,
          tileHeight
        );

        createSpriteFromTileDescription(
          sceneGraph,
          tilePosition,
          tileDescription,
          assetManager
        );
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

  void TiledSceneBuilder::createSpriteFromTileDescription(
    SceneGraph& sceneGraph,
    const Vector2f& position,
    const TileDescription& tileDescription,
    const AssetManager& assetManager
  )
  {
    const sf::Texture* texture = assetManager.getTexture(
      tileDescription.getTextureKey()
    );

    auto spriteObj = MakeUnique<SpriteGameObject>(
      texture,
      tileDescription.getTextureRect()
    );

    // Set origin to bottom-center so the computed isometric position
    // corresponds to the tile's bottom center (common convention).
    const sf::IntRect rect = tileDescription.getTextureRect();
    spriteObj->getSprite().setOrigin(
      sf::Vector2f(
        static_cast<float>(rect.size.x) * 0.5f,
        static_cast<float>(rect.size.y)
      )
    );

    spriteObj->setPosition(position);

    sceneGraph.getRoot()->addChild(std::move(spriteObj));
  }
}