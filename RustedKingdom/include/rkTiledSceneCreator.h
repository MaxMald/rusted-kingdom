#pragma once

#include "rkPrerequisites.h"
#include "rkDependenciesLocator.h"

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
      ComponentFactoryLocator& componentFactoryLocator,
      SceneGraph& sceneGraph
    );
  }
}