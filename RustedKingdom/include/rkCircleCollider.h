#pragma once

#include "rkCollider.h"

namespace rk
{
  class CircleCollider : public Collider
  {
  public:
    CircleCollider(GameObject& gameObject);
    virtual ~CircleCollider();

    float getRadius() const;
    void setRadius(float radius);

    virtual bool checkCollision(const Collider& other) const override;
    virtual bool checkCollision(const Vector2f& point) const override;

  private:
    float m_radius;
    float m_radiusPow2;

    bool checkCollisionWithCircle(const CircleCollider& other) const;
  };
}