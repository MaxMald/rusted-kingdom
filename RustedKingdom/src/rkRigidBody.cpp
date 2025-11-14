#include "rkRigidBody.h"

namespace rk
{
  RigidBody::RigidBody(rigidBodyType::Type type) :
    m_mass(1.0f),
    m_type(type),
    m_position(0.0f, 0.0f),
    m_velocity(0.0f, 0.0f)
  {
  }

  RigidBody::~RigidBody()
  {
  }

  void RigidBody::update(float deltaTime)
  {
    if (m_type == rigidBodyType::Kinematic)
      m_position += m_velocity * deltaTime;
  }
}