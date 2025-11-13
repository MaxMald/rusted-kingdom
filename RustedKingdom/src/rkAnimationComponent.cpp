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
    Component(gameObject, componentType::Type::Animation),
    m_spriteComponent(nullptr),
    m_animationStateMachine(std::move(animationStateMachine))
  {
    if (!gameObject.hasComponent(componentType::Type::Sprite))
    {
      throw RuntimeErrorException(
        "AnimationComponent error: Associated GameObject does not have a "
        "SpriteComponent."
      );
    }

    m_spriteComponent = gameObject.getComponent<SpriteComponent>(
      componentType::Type::Sprite
    );
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

  void AnimationStateMachineComponent::onUpdate(float deltaTime)
  {
    m_animationStateMachine->update(
      deltaTime,
      m_spriteComponent->getSprite()
    );
  }
}