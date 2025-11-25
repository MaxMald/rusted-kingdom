#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class AssetManager;

  namespace tiledMapAssetLoader
  {
    bool loadTiledMapAssets(
      AssetManager& assetManager,
      const String& tiledMapKey
    );
  }
}
