#include "rkCircleColliderDrawer.h"

#include "rkCollider.h"
#include "rkCircleCollider.h"

namespace rk
{
  CircleColliderDrawer::CircleColliderDrawer() :
    m_sfmlCircleShape()
  {
  }

  CircleColliderDrawer::~CircleColliderDrawer()
  {
  }

  void CircleColliderDrawer::draw(
    sf::RenderWindow& window,
    const Collider& collider,
    const sf::Color& color
  )
  {
    if (collider.getType() != colliderType::Circle)
      return;

    const CircleCollider* circleCollider =
      dynamic_cast<const CircleCollider*>(&collider);

    if (!circleCollider)
      return;

    float radius = circleCollider->getRadius();

    m_sfmlCircleShape.setRadius(radius);
    m_sfmlCircleShape.setFillColor(sf::Color::Transparent);
    m_sfmlCircleShape.setOutlineColor(color);
    m_sfmlCircleShape.setOutlineThickness(1.0f);
    m_sfmlCircleShape.setOrigin(sf::Vector2f(radius, radius));
    m_sfmlCircleShape.setPosition(circleCollider->getPosition() + circleCollider->getCenter());

    window.draw(m_sfmlCircleShape);
  }
}