#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class TiledClassApplierMapper;
  class AssetManager;
  class SceneGraph;

  namespace tiledSceneCreator
  {
    void create(
      const String& tiledMapKey,
      const AssetManager& assetManager,
      TiledClassApplierMapper& tiledClassApplierMapper,
      SceneGraph& sceneGraph
    );
  }
}