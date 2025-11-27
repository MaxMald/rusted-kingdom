#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkComponent.h"
#include "rkColliderType.h"

using sf::Vector2f;

namespace rk
{
  class Collider;
  class PhysicWorld;

  class ColliderComponent : public Component
  {
  public:
    ColliderComponent(
      GameObject& gameObject,
      PhysicWorld& physicWorld,
      Collider* collider
    );
    virtual ~ColliderComponent();

    const Vector2f& getCenter() const;
    void setCenter(const Vector2f& center);
    const colliderType::Type getColliderType() const;
    void setDebug(bool debug) { m_debug = debug; }

    bool checkCollision(const ColliderComponent& other) const;
    bool checkCollision(const Vector2f& point) const;

  protected:
    Collider* m_collider;
    PhysicWorld& m_physicWorld;
    bool m_debug;
  };
}