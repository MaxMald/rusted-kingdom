#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkRigidBodyType.h"

using sf::Vector2f;

namespace rk
{
  class RigidBody : public NonCopyable
  {
  public:
    RigidBody(rigidBodyType::Type type);
    ~RigidBody();

    float getMass() const { return m_mass; }
    void setMass(float mass){ m_mass = mass; }
    rigidBodyType::Type getType() const { return m_type; }
    const Vector2f& getPosition() const { return m_position; }
    void setPosition(const Vector2f& position) { m_position = position; }
    const Vector2f& getVelocity() const { return m_velocity; }
    void setVelocity(const Vector2f& velocity) { m_velocity = velocity; }

    void update(float deltaTime);

  private:
    float m_mass;
    rigidBodyType::Type m_type;
    Vector2f m_position;
    Vector2f m_velocity;
  };
}