#include "rkAnimationStateTransition.h"

namespace rk
{
  AnimationStateTransition::AnimationStateTransition(
    AnimationState* fromState,
    AnimationState* toState
  ) :
    m_fromState(fromState),
    m_toState(toState)
  {
  }

  AnimationStateTransition::~AnimationStateTransition()
  {
  }

  AnimationStateTransition::AnimationStateTransition(
    const AnimationStateTransition& other
  ) :
    m_fromState(other.m_fromState),
    m_toState(other.m_toState)
  {
  }

  AnimationStateTransition& AnimationStateTransition::operator=(
    const AnimationStateTransition& other
    )
  {
    if (this != &other)
    {
      m_fromState = other.m_fromState;
      m_toState = other.m_toState;
    }

    return *this;
  }

  AnimationStateTransition::AnimationStateTransition(
    AnimationStateTransition&& other
  ) noexcept :
    m_fromState(other.m_fromState),
    m_toState(other.m_toState)
  {
    other.m_fromState = nullptr;
    other.m_toState = nullptr;
  }

  AnimationStateTransition& AnimationStateTransition::operator=(
    AnimationStateTransition&& other
    ) noexcept
  {
    if (this != &other)
    {
      m_fromState = other.m_fromState;
      m_toState = other.m_toState;
      other.m_fromState = nullptr;
      other.m_toState = nullptr;
    }

    return *this;
  }
}