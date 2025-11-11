#include "rkAnimationStateTransition.h"

namespace rk
{
  AnimationStateTransition::AnimationStateTransition(
    AnimationState* fromState,
    AnimationState* toState,
    std::function<bool()> condition
  )
    : m_fromState(fromState)
    , m_toState(toState)
    , m_condition(condition)
  {
  }

  AnimationStateTransition::~AnimationStateTransition()
  {
  }

  AnimationStateTransition::AnimationStateTransition(
    const AnimationStateTransition& other
  ) :
    m_fromState(other.m_fromState),
    m_toState(other.m_toState),
    m_condition(other.m_condition)
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
      m_condition = other.m_condition;
    }

    return *this;
  }

  AnimationStateTransition::AnimationStateTransition(
    AnimationStateTransition&& other
  ) noexcept :
    m_fromState(other.m_fromState),
    m_toState(other.m_toState),
    m_condition(std::move(other.m_condition))
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
      m_condition = std::move(other.m_condition);
      other.m_fromState = nullptr;
      other.m_toState = nullptr;
    }

    return *this;
  }
}