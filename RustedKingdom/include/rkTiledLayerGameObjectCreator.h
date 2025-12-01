#pragma once

#include "rkPrerequisites.h"

namespace tmr
{
  class TiledMap;
  class Layer;
}

namespace rk
{
  class GameObject;
  class SceneGraph;

  namespace tiledLayerGameObjectCreator
  {
    GameObject* create(
      const tmr::TiledMap*,
      const tmr::Layer*,
      SceneGraph&
    );

    GameObject* createForOrthogonalMap(
      const tmr::Layer*,
      SceneGraph&
    );

    GameObject* createForIsometricMap(
      const tmr::Layer*,
      SceneGraph&
    );
  }
}