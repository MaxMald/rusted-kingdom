#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class SpriteComponentFactory;
  class AssetManager;
  class SceneGraph;

  namespace tiledSceneCreator
  {
    void create(
      const String& tiledMapKey,
      const AssetManager& assetManager,
      SpriteComponentFactory& spriteComponentFactory,
      SceneGraph& sceneGraph
    );
  }
}