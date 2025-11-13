#pragma once

#include <functional>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class AnimationState;
  class AnimationStateMachine;

  class AnimationStateTransition : public NonCopyable
  {
  public:
    AnimationStateTransition(
      AnimationState& fromState,
      AnimationState& toState
    );
    virtual ~AnimationStateTransition();

    AnimationState& getFromState() const { return m_fromState; }
    AnimationState& getToState() const { return m_toState; }
    
    virtual bool canTransition(const AnimationStateMachine&) const = 0;

  private:
    AnimationState& m_fromState;
    AnimationState& m_toState;
  };
}