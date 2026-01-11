#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkComponent.h"
#include "rkRigidBodyType.h"

using sf::Vector2f;

namespace rk
{
  class PhysicWorld;
  class RigidBody;

  class RigidBodyComponent : public Component
  {
  public:
    RigidBodyComponent(
      GameObject&,
      PhysicWorld&,
      rigidBodyType::Type
    );
    virtual ~RigidBodyComponent();

    void setMass(float mass);
    float getMass() const;
    void setVelocity(const Vector2f& velocity);
    const Vector2f& getVelocity() const;
    rigidBodyType::Type getType() const;
    const Vector2f& getPosition() const;

  protected:
    RigidBody* m_rigidBody;
    PhysicWorld& m_physicWorld;
  };
}