#include "rkAnimationState.h"
#include "rkAnimation.h"
#include "rkAnimationStateTransition.h"

namespace rk
{
  AnimationState::AnimationState(Animation& animation) :
    m_animation(&animation),
    m_isActive(false)
  {
  }

  AnimationState::~AnimationState()
  {
    for (auto transition : m_transitions)
      delete transition;
    m_transitions.clear();
  }

  Animation& AnimationState::getAnimation()
  {
    return *m_animation;
  }

  const Animation& AnimationState::getAnimation() const
  {
    return *m_animation;
  }

  void AnimationState::addTransition(const AnimationStateTransition* transition)
  {
    m_transitions.push_back(transition);
  }

  void AnimationState::onEnter()
  {
    m_isActive = true;
    m_animation->reset();
    m_animation->play();
  }

  void AnimationState::update(float deltaTime)
  {
    if (m_isActive)
      m_animation->update(deltaTime);
  }

  void AnimationState::onExit()
  {
    m_animation->stop();
    m_isActive = false;
  }
}