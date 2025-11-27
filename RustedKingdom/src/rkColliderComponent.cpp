#include "rkColliderComponent.h"
#include "rkPhysicWorld.h"
#include "rkCollider.h"
#include "rkGameObject.h"

namespace rk
{
  ColliderComponent::ColliderComponent(
    GameObject& gameObject,
    PhysicWorld& physicWorld,
    Collider* collider
  ) :
    Component(gameObject, componentType::Type::Collider),
    m_physicWorld(physicWorld),
    m_collider(collider),
    m_debug(false)
  {
    if (collider == nullptr)
    {
      throw InvalidArgumentException(
        "ColliderComponent::ColliderComponent: collider argument is null."
      );
    }
  }

  ColliderComponent::~ColliderComponent()
  {
    m_physicWorld.destroyCollider(m_collider);
  }

  const Vector2f& ColliderComponent::getCenter() const
  {
    return m_collider->getCenter();
  }

  void ColliderComponent::setCenter(const Vector2f& center)
  {
    m_collider->setCenter(m_gameObject->getWorldPosition() + center);
  }

  const colliderType::Type ColliderComponent::getColliderType() const
  {
    return m_collider->getType();
  }

  bool ColliderComponent::checkCollision(const ColliderComponent& other) const
  {
    return m_collider->checkCollision(*other.m_collider);
  }

  bool ColliderComponent::checkCollision(const Vector2f& point) const
  {
    return m_collider->checkCollision(point);
  }
}