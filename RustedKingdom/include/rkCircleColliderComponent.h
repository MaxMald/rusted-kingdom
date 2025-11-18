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
    void setDebug(bool debug) { m_debug = debug; }

    virtual void onDraw(
      sf::RenderTarget& target,
      sf::RenderStates states
    ) const override;

  protected:
    CircleCollider* m_circleCollider;
    bool m_debug;

    void debugCircleCollider(sf::RenderTarget& target) const;
  };
}