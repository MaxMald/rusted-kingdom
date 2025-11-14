#include "rkCircleCollider.h"

namespace rk
{
  CircleCollider::CircleCollider() : 
    Collider(colliderType::Circle), 
    m_center(0.0f, 0.0f), 
    m_radius(0.0f)
  {
  }

  CircleCollider::CircleCollider(const Vector2f& center, float radius) : 
    Collider(colliderType::Circle),
    m_center(center),
    m_radius(radius)
  {
  }

  CircleCollider::CircleCollider(const CircleCollider& other) : 
    Collider(colliderType::Circle),
    m_center(other.m_center),
    m_radius(other.m_radius)
  {
  }

  CircleCollider::CircleCollider(CircleCollider&& other) noexcept :
    Collider(colliderType::Circle),
    m_center(std::move(other.m_center)),
    m_radius(other.m_radius)
  {
  }

  CircleCollider::~CircleCollider()
  {
  }

  CircleCollider& CircleCollider::operator=(const CircleCollider& other)
  {
    if (this != &other)
    {
      m_center = other.m_center;
      m_radius = other.m_radius;
    }
    return *this;
  }

  CircleCollider& CircleCollider::operator=(CircleCollider&& other) noexcept
  {
    if (this != &other)
    {
      m_center = std::move(other.m_center);
      m_radius = other.m_radius;
    }
    return *this;
  }

  const Vector2f& CircleCollider::getCenter() const
  {
    return m_center;
  }

  void CircleCollider::setCenter(const Vector2f& center)
  {
    m_center = center;
  }

  float CircleCollider::getRadius() const
  {
    return m_radius;
  }

  void CircleCollider::setRadius(float radius)
  {
    m_radius = radius;
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

  bool CircleCollider::checkCollisionWithCircle(const CircleCollider& other) const
  {
    Vector2f diff = other.getCenter() - getCenter();
    float distanceSquared = diff.lengthSquared();
    float radiusSum = m_radius + other.getRadius();
    return distanceSquared <= (radiusSum * radiusSum);
  }
}