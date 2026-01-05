#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkRigidBodyType.h"

using sf::Vector2f;

namespace rk
{
  class PhysicWorld;
  class RigidBodyComponent;
  class GameObject;

  namespace rigidBodyComponentFactory
  {
    UniquePtr<RigidBodyComponent> create(
      GameObject& gameObject,
      rigidBodyType::Type type,
      bool debug = false
    );
  }
}