#include "rkRigidBodyDebuggedComponent.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Color.hpp>

#include "rkCircleCollider.h"
#include "rkRigidBody.h"

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

    debugVelocityArrow(
      target,
      states,
      m_rigidBody->getPosition(),
      m_rigidBody->getVelocity()
    );
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

  void RigidBodyDebuggedComponent::debugVelocityArrow(
    sf::RenderTarget& target,
    sf::RenderStates,
    const Vector2f& position,
    const Vector2f& velocity
  ) const
  {
    if (velocity.x == 0.f && velocity.y == 0.f)
      return;

    const float velocityScale = 1.0f;
    Vector2f end = position + velocity * velocityScale;

    sf::Vertex v1;
    v1.position = position;
    v1.color = sf::Color::Red;

    sf::Vertex v2;
    v2.position = end;
    v2.color = sf::Color::Red;

    sf::Vertex line[] = {v1, v2};
    target.draw(line, 2, sf::PrimitiveType::Lines);
  }
}