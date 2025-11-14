#pragma once

#include "rkCollider.h"

namespace rk
{
  class CircleCollider : public Collider
  {
  public:
    CircleCollider();
    CircleCollider(const Vector2f& center, float radius);
    CircleCollider(const CircleCollider&);
    CircleCollider(CircleCollider&&) noexcept;
    virtual ~CircleCollider();

    CircleCollider& operator=(const CircleCollider&);
    CircleCollider& operator=(CircleCollider&&) noexcept;

    virtual const Vector2f& getCenter() const override;
    virtual void setCenter(const Vector2f& center) override;
    float getRadius() const;
    void setRadius(float radius);

    virtual bool checkCollision(const Collider& other) const override;

  private:
    Vector2f m_center;
    float m_radius;

    bool checkCollisionWithCircle(const CircleCollider& other) const;
  };
}