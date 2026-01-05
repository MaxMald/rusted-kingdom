#pragma once

#include "rkPrerequisites.h"

#include <SFML/Graphics/Rect.hpp>

namespace rk
{
  class SpriteComponent;
  class AssetManager;
  class GameObject;

  namespace spriteComponentFactory
  {
    UniquePtr<SpriteComponent> createSpriteComponent(
      GameObject& gameObject,
      const String& textureKey
    );

    UniquePtr<SpriteComponent> createSpriteComponent(
      GameObject& gameObject,
      const String& textureKey,
      const sf::IntRect& textureRect
    );
  }
}