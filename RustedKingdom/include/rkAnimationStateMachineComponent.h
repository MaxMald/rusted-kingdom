#pragma once

#include "rkComponent.h"
#include "rkAnimationStateMachine.h"

using sf::Vector2i;

namespace sf
{
  class Texture;
}

namespace rk
{
  class SpriteComponent;
  class Blackboard;

  class AnimationStateMachineComponent : public Component
  {
  public:
    AnimationStateMachineComponent(
      GameObject& gameObject,
      UniquePtr<AnimationStateMachine> animationStateMachine
    );
    virtual ~AnimationStateMachineComponent();

    Blackboard& getBlackboard();
    const Blackboard& getBlackboard() const;

  protected:
    virtual void onUpdate(float deltaTime) override;

  private:
    SpriteComponent* m_spriteComponent;
    UniquePtr<AnimationStateMachine> m_animationStateMachine;
  };
}