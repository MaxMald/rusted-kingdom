#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

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
using sf::FloatRect;

namespace rk
{
  class GameObject;
  class SceneGraph;

  namespace minimapTextureCreator
  {
    sf::Texture create(
      const tmr::TiledMap*,
      const Vector<GameObject*>& mapGameObjects,
      const FloatRect& mapBounds,
      const Vector2f& minimapSize,
      SceneGraph&
    );
  }
}