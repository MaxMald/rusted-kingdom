#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace tmr
{
  class TiledMap;
}

namespace rk
{
  class GameObject;
  class SceneGraph;

  namespace minimapUtilities
  {
    static constexpr const char* MINIMAP_TEXTURE_KEY = "__MINIMAP_TEXTURE__";

    void prepare(
      GameObject* minimapGameObject,
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph
    );
  }
}