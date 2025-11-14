#include "rkRigidBody.h"
#include "rkGameObject.h"

using sf::Transform;

namespace rk
{
  RigidBody::RigidBody(rigidBodyType::Type type, GameObject& gameObject) :
    m_gameObject(gameObject),
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

  void RigidBody::syncRigidBodyPositionToGameObject()
  {
    GameObject* parent = m_gameObject.getParent();
    Transform parentWorldTransform = parent
      ? parent->getWorldTransform()
      : Transform::Identity;

    m_gameObject.setPosition(
      parentWorldTransform
      .getInverse()
      .transformPoint(m_position)
    );
  }

  void RigidBody::syncGameObjectPositionToRigidBody()
  {
    m_position = m_gameObject
      .getWorldTransform()
      .transformPoint(m_gameObject.getPosition());
  }
}