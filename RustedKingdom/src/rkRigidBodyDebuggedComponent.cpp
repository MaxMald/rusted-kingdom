#include "rkRigidBodyDebuggedComponent.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "rkCircleCollider.h"

using sf::Vector2f;

namespace rk
{
  RigidBodyDebuggedComponent::RigidBodyDebuggedComponent(
    GameObject& gameObject,
    PhysicWorld& physicWorld,
    rigidBodyType::Type type,
    UniquePtr<Collider> collider
  ) :
    RigidBodyComponent(
      gameObject,
      physicWorld,
      type,
      std::move(collider)
    )
  {
  }

  RigidBodyDebuggedComponent::~RigidBodyDebuggedComponent()
  {
  }

  void RigidBodyDebuggedComponent::onDraw(
    sf::RenderTarget& target,
    sf::RenderStates states
  ) const
  {
    if (m_collider && m_collider->getType() == colliderType::Circle)
    {
      const CircleCollider* circleCollider = static_cast<const CircleCollider*>(
        m_collider.get()
      );

      debugCircleCollider(target, states, *circleCollider);
    }
  }
  void RigidBodyDebuggedComponent::debugCircleCollider(
    sf::RenderTarget& target,
    sf::RenderStates,
    const CircleCollider& circleCollider
  ) const
  {
    sf::CircleShape debugShape(circleCollider.getRadius());
    debugShape.setOrigin(
      Vector2f(circleCollider.getRadius(), circleCollider.getRadius())
    );
    debugShape.setPosition(circleCollider.getCenter());
    debugShape.setFillColor(sf::Color::Transparent);
    debugShape.setOutlineColor(sf::Color::Green);
    debugShape.setOutlineThickness(2.0f);
    target.draw(debugShape);
  }
}