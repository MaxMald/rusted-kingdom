#include "rkCircleColliderComponent.h"

#include <SFML/Graphics/CircleShape.hpp>

#include "rkCircleCollider.h"
#include "rkPhysicWorld.h"

namespace rk
{
  CircleColliderComponent::CircleColliderComponent(
    GameObject& gameObject,
    PhysicWorld& physicWorld,
    CircleCollider* circleCollider
  ) :
    ColliderComponent(gameObject, physicWorld, circleCollider),
    m_circleCollider(circleCollider)
  {
  }

  float CircleColliderComponent::getRadius() const
  {
    return m_circleCollider->getRadius();
  }

  void CircleColliderComponent::setRadius(float radius)
  {
    m_circleCollider->setRadius(radius);
  }

  void CircleColliderComponent::onDraw(
    sf::RenderTarget& target,
    sf::RenderStates
  ) const
  {
    if (m_debug)
      debugCircleCollider(target);
  }

  void CircleColliderComponent::debugCircleCollider(sf::RenderTarget& target) const
  {
    const float radius = m_circleCollider->getRadius();
    const Vector2f position = m_circleCollider->getPosition() 
      + m_circleCollider->getCenter();

    sf::CircleShape circle(radius);
    circle.setPosition(position - Vector2f(radius, radius));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1.f);

    target.draw(circle);
  }
}