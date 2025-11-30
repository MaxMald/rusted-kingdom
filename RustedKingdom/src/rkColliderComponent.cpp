#include "rkColliderComponent.h"

#include <SFML/Graphics/CircleShape.hpp>

#include "rkPhysicWorld.h"
#include "rkCollider.h"
#include "rkCircleCollider.h"
#include "rkGameObject.h"

namespace rk
{
  ColliderComponent::ColliderComponent(
    GameObject& gameObject,
    PhysicWorld& physicWorld,
    Collider* collider
  ) :
    Component(gameObject),
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

  const Collider* ColliderComponent::getCollider() const
  {
    return m_collider;
  }

  bool ColliderComponent::checkCollision(const ColliderComponent& other) const
  {
    return m_collider->checkCollision(*other.m_collider);
  }

  bool ColliderComponent::checkCollision(const Vector2f& point) const
  {
    return m_collider->checkCollision(point);
  }

  void ColliderComponent::onDraw(
    RenderTarget& target,
    RenderStates states
  ) const
  {
    if (!m_debug)
      return;

    if (m_collider->getType() == colliderType::Circle)
    {
      debugCircleCollider(
        static_cast<const CircleCollider*>(m_collider),
        target
      );
    }
  }

  void ColliderComponent::debugCircleCollider(
    const CircleCollider* circleCollider,
    RenderTarget& target
  ) const
  {
    const float radius = circleCollider->getRadius();
    const Vector2f position = circleCollider->getPosition()
      + circleCollider->getCenter();

    sf::CircleShape circle(radius);
    circle.setPosition(position - Vector2f(radius, radius));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1.f);

    target.draw(circle);
  }
}