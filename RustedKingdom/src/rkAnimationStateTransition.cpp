#include "rkAnimationStateTransition.h"

namespace rk
{
  AnimationStateTransition::AnimationStateTransition(
    AnimationState& fromState,
    AnimationState& toState
  ) :
    m_fromState(fromState),
    m_toState(toState)
  {
  }

  AnimationStateTransition::~AnimationStateTransition()
  {
  }
}