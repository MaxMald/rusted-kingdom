#pragma once

#include "rkScriptComponent.h"

namespace rk
{
  class AnimationStateMachineComponent;
  class RigidBodyComponent;

  class UnitAnimationControllerScript : public ScriptComponent
  {
  public:
    UnitAnimationControllerScript(GameObject& gameObject);
    virtual ~UnitAnimationControllerScript();

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;

  private:
    AnimationStateMachineComponent* m_animationComponent;
    RigidBodyComponent* m_rigidBodyComponent;
  };
}
