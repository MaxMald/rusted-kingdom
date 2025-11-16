#pragma once

#include "rkScriptComponent.h"

namespace rk
{
  class AnimationStateMachineComponent;
  class RigidBodyComponent;

  class LuciusAnimation : public ScriptComponent
  {
  public:
    LuciusAnimation(GameObject& gameObject);
    virtual ~LuciusAnimation();

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;

  private:
    AnimationStateMachineComponent* m_animationComponent;
    RigidBodyComponent* m_rigidBodyComponent;
  };
}
