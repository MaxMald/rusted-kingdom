#include "rkAnimationStateMachineComponent.h"
#include "rkGameObject.h"
#include "rkEightDirectionsSpriteSheetAnimation.h"
#include "rkAnimationStateMachine.h"
#include "rkBlackboard.h"
#include "rkSpriteComponent.h"

namespace rk
{
  AnimationStateMachineComponent::AnimationStateMachineComponent(
    GameObject& gameObject,
    UniquePtr<AnimationStateMachine> animationStateMachine
  ) :
    Component(gameObject),
    m_spriteComponent(nullptr),
    m_animationStateMachine(std::move(animationStateMachine))
  {
    m_spriteComponent = gameObject.getComponent<SpriteComponent>();
  }

  AnimationStateMachineComponent::~AnimationStateMachineComponent()
  {
  }

  Blackboard& AnimationStateMachineComponent::getBlackboard()
  {
    return m_animationStateMachine->getBlackboard();
  }

  const Blackboard& AnimationStateMachineComponent::getBlackboard() const
  {
    return m_animationStateMachine->getBlackboard();
  }

  const AnimationState* AnimationStateMachineComponent::getCurrentState() const
  {
    return m_animationStateMachine->getCurrentState();
  }

  void AnimationStateMachineComponent::onUpdate(float deltaTime)
  {
    m_animationStateMachine->update(
      deltaTime,
      m_spriteComponent->getSprite()
    );
  }
}