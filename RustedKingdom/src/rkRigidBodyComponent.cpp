#include "rkRigidBodyComponent.h"
#include "rkRigidBody.h"
#include "rkPhysicWorld.h"
#include "rkGameObject.h"

namespace rk
{
  RigidBodyComponent::RigidBodyComponent(
    GameObject& gameObject,
    PhysicWorld& physicWorld,
    rigidBodyType::Type type
  ) :
    Component(gameObject, componentType::RigidBody),
    m_physicWorld(physicWorld),
    m_rigidBody(nullptr)
  {

    m_rigidBody = physicWorld.createRigidBody(
      type,
      gameObject
    );
  }

  RigidBodyComponent::~RigidBodyComponent()
  {
    if (m_rigidBody)
    {
      m_physicWorld.destroyRigidBody(m_rigidBody);
      m_rigidBody = nullptr;
    }
  }

  void RigidBodyComponent::setMass(float mass)
  {
    if (m_rigidBody)
      m_rigidBody->setMass(mass);
  }

  float RigidBodyComponent::getMass() const
  {
    if (m_rigidBody)
      return m_rigidBody->getMass();
    return 0.0f;
  }

  void RigidBodyComponent::setVelocity(const Vector2f& velocity)
  {
    if (m_rigidBody)
      m_rigidBody->setVelocity(velocity);
  }

  const Vector2f& RigidBodyComponent::getVelocity() const
  {
    if (m_rigidBody)
      return m_rigidBody->getVelocity();

    static Vector2f zeroVelocity(0.0f, 0.0f);
    return zeroVelocity;
  }
}