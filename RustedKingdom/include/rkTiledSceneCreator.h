#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class TiledObjectCreator;
  class SpriteComponentFactory;
  class AssetManager;
  class SceneGraph;

  namespace tiledSceneCreator
  {
    void create(
      const String& tiledMapKey,
      const AssetManager& assetManager,
      TiledObjectCreator& tiledObjectCreator,
      SpriteComponentFactory& spriteComponentFactory,
      SceneGraph& sceneGraph
    );
  }
}