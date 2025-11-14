#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkComponent.h"
#include "rkRigidBodyType.h"

using sf::Vector2f;

namespace rk
{
  class PhysicWorld;
  class RigidBody;
  class Collider;

  class RigidBodyComponent : public Component
  {
  public:
    RigidBodyComponent(
      GameObject&,
      PhysicWorld&,
      rigidBodyType::Type,
      UniquePtr<Collider>
    );
    virtual ~RigidBodyComponent();

    void setMass(float mass);
    float getMass() const;
    void setVelocity(const Vector2f& velocity);
    const Vector2f& getVelocity() const;
    Collider& getCollider() { return *m_collider; }
    const Collider& getCollider() const { return *m_collider; }

  protected:
    RigidBody* m_rigidBody;
    UniquePtr<Collider> m_collider;
    PhysicWorld& m_physicWorld;
  };
}