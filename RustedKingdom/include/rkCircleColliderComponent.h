#pragma once

#include "rkColliderComponent.h"

namespace rk
{
  class CircleCollider;

  class CircleColliderComponent : public ColliderComponent
  {
  public:
    CircleColliderComponent(
      GameObject& gameObject,
      PhysicWorld& physicWorld,
      CircleCollider* circleCollider
    );
    virtual ~CircleColliderComponent() {}

    float getRadius() const;
    void setRadius(float radius);

    virtual void onDraw(
      sf::RenderTarget& target,
      sf::RenderStates states
    ) const override;

  protected:
    CircleCollider* m_circleCollider;

    void debugCircleCollider(sf::RenderTarget& target) const;
  };
}