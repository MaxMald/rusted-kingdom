#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class TiledClassApplierMapper;
  class SpriteComponentFactory;
  class AssetManager;
  class SceneGraph;

  namespace tiledSceneCreator
  {
    void create(
      const String& tiledMapKey,
      const AssetManager& assetManager,
      TiledClassApplierMapper& tiledClassApplierMapper,
      SpriteComponentFactory& spriteComponentFactory,
      SceneGraph& sceneGraph
    );
  }
}