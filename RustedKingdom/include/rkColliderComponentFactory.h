#pragma once

#include "rkPrerequisites.h"

#include <SFML/System/Vector2.hpp>

using sf::Vector2f;

namespace rk
{
  class GameObject;
  class PhysicWorld;
  class ColliderComponent;

  namespace colliderComponentFactory
  {
    UniquePtr<ColliderComponent> createCircle(
      GameObject& gameObject,
      const Vector2f& center,
      float radius,
      const String& colliderGroupKey
    );
  }
}