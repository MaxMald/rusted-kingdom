#include "rkCircleCollider.h"

namespace rk
{
  CircleCollider::CircleCollider(GameObject& gameObject) :
    Collider(gameObject, colliderType::Circle),
    m_radius(1.0f),
    m_radiusPow2(1.0f)
  {
  }

  CircleCollider::~CircleCollider()
  {
  }

  float CircleCollider::getRadius() const
  {
    return m_radius;
  }

  void CircleCollider::setRadius(float radius)
  {
    m_radius = radius;
    m_radiusPow2 = radius * radius;
  }

  bool CircleCollider::checkCollision(const Collider& other) const
  {
    if (other.getType() == colliderType::Circle)
    {
      return checkCollisionWithCircle(static_cast<const CircleCollider&>(other));
    }
    else if (other.getType() == colliderType::Undefined)
    {
      return false;
    }

    throw RuntimeErrorException(
      "CircleCollider::checkCollision: Unsupported collider type."
    );
  }

  bool CircleCollider::checkCollision(const Vector2f& point) const
  {
    Vector2f thisPosition = m_position + m_center;
    Vector2f diff = point - thisPosition;
    return diff.lengthSquared() <= m_radiusPow2;
  }

  bool CircleCollider::checkCollisionWithCircle(const CircleCollider& other) const
  {
    Vector2f thisPosition = m_position + m_center;
    Vector2f otherPosition = other.m_position + other.m_center;
    Vector2f diff = thisPosition - otherPosition;
    float distanceSquared = diff.lengthSquared();
    float radiusSum = m_radius + other.getRadius();
    return distanceSquared <= (radiusSum * radiusSum);
  }
}