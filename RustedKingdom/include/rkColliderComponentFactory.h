#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

using sf::Vector2f;

namespace rk
{
  class GameObject;
  class PhysicWorld;
  class ColliderComponent;

  class ColliderComponentFactory : public NonCopyable
  {
  public:
    ColliderComponentFactory(PhysicWorld& physicWorld);
    ~ColliderComponentFactory();

    UniquePtr<ColliderComponent> createCircle(
      GameObject& gameObject,
      const Vector2f& center,
      float radius,
      const String& colliderGroupKey
    );
    
  private:
    PhysicWorld& m_physicWorld;
  };
}