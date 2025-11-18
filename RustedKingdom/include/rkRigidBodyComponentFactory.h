#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkRigidBodyType.h"

using sf::Vector2f;

namespace rk
{
  class PhysicWorld;
  class RigidBodyComponent;
  class GameObject;

  class RigidBodyComponentFactory : public NonCopyable
  {
  public:
    RigidBodyComponentFactory(PhysicWorld&);
    ~RigidBodyComponentFactory();

    UniquePtr<RigidBodyComponent> create(
      GameObject& gameObject,
      rigidBodyType::Type type,
      bool debug = false
    );

  private:
    PhysicWorld& m_physicWorld;
  };
}