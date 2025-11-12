#pragma once

#include "rkPrerequisites.h"
#include <functional>

namespace rk
{
  class AnimationState;
  class AnimationStateMachine;

  class AnimationStateTransition
  {
  public:
    AnimationStateTransition(
      AnimationState* fromState,
      AnimationState* toState
    );
    virtual ~AnimationStateTransition();

    AnimationStateTransition(const AnimationStateTransition&);
    AnimationStateTransition& operator=(const AnimationStateTransition&);

    AnimationStateTransition(AnimationStateTransition&&) noexcept;
    AnimationStateTransition& operator=(AnimationStateTransition&&) noexcept;

    AnimationState* getFromState() const { return m_fromState; }
    AnimationState* getToState() const { return m_toState; }
    
    virtual bool canTransition(const AnimationStateMachine&) const = 0;

  private:
    AnimationState* m_fromState;
    AnimationState* m_toState;
  };
}