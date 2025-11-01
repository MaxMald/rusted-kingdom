#include "rkTiledMapBuilder.h"

namespace rk
{
  void TiledSceneBuilder::buildFromTiledMap(
    SceneGraph& sceneGraph,
    const TiledMap& tiledMap,
    AssetManager& assetManager
  )
  {
  }

  Vector2f TiledSceneBuilder::computeTilePositionIsometric(
    const Int32& col,
    const Int32& row,
    const Int32& tileWidth,
    const Int32& tileHeight
  )
  {
    return Vector2f();
  }
}