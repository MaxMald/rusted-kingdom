#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class AssetManager;
  class SceneGraph;

  namespace tiledSceneCreator
  {
    void create(
      const String& tiledMapKey,
      const AssetManager&,
      SceneGraph&
    );
  }
}