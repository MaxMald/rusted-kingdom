#pragma once

#include "rkComponent.h"

namespace rk
{
  class AnimationComponent : public Component
  {
  public:
    AnimationComponent(GameObject& gameObject);
    virtual ~AnimationComponent();
  protected:
    virtual void onUpdate(float deltaTime) override;
  };
}