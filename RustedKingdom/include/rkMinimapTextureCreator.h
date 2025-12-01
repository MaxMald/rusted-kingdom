#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"

namespace sf
{
  class Texture;
}

namespace tmr
{
  class TiledMap;
}

using sf::Vector2f;

namespace rk
{
  class SceneGraph;

  namespace minimapTextureCreator
  {
    sf::Texture create(
      const tmr::TiledMap*,
      SceneGraph&,
      const Vector2f& size
    );
  }
}