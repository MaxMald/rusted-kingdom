#pragma once

#include "rkRigidBodyComponent.h"

namespace rk
{
  class RigidBodyDebuggedComponent : public RigidBodyComponent
  {
  public:
    RigidBodyDebuggedComponent(
      GameObject& gameObject,
      PhysicWorld& physicWorld,
      rigidBodyType::Type type
    );
    virtual ~RigidBodyDebuggedComponent();

  protected:
    virtual void onDraw(
      sf::RenderTarget& target,
      sf::RenderStates states
    ) const override;

  private:
    void debugVelocityArrow(
      sf::RenderTarget& target,
      sf::RenderStates states,
      const Vector2f& position,
      const Vector2f& velocity
    ) const;
  };
}