#include "rkAnimationState.h"
#include "rkAnimation.h"
#include "rkAnimationStateTransition.h"

namespace rk
{
  AnimationState::AnimationState(
    const String& key,
    UniquePtr<Animation> animation
  ) :
    m_key(key),
    m_animation(std::move(animation))
  {
  }

  AnimationState::~AnimationState()
  {
    m_transitions.clear();
  }

  void AnimationState::addTransition(
    UniquePtr<AnimationStateTransition> transition
  )
  {
    m_transitions.push_back(std::move(transition));
  }

  void AnimationState::onEnter(Sprite& sprite)
  {
    m_animation->prepareSprite(sprite);
    m_animation->reset();
    m_animation->play();
  }

  void AnimationState::update(float deltaTime)
  {
    m_animation->update(deltaTime);
  }

  void AnimationState::onExit()
  {
    m_animation->stop();
  }
}