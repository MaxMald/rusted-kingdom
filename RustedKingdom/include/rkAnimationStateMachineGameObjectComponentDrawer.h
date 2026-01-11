#pragma once

#include "rkAGameObjectComponentDrawer.h"

namespace rk
{
  class AnimationState;

  class AnimationStateMachineGameObjectComponentDrawer : 
    public AGameObjectComponentDrawer
  {
  public:
    AnimationStateMachineGameObjectComponentDrawer();
    virtual ~AnimationStateMachineGameObjectComponentDrawer();

  protected:
    void onDraw(Component& component, sf::RenderWindow& window) override;

    void drawAnimationState(const AnimationState* state);
  };
}