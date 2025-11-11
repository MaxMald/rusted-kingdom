#pragma once

#include "rkPrerequisites.h"
#include <functional>

namespace rk
{
  class AnimationState;

  class AnimationStateTransition
  {
  public:
    AnimationStateTransition(
      AnimationState* fromState,
      AnimationState* toState,
      std::function<bool()> condition
    );
    ~AnimationStateTransition();

    AnimationStateTransition(const AnimationStateTransition&);
    AnimationStateTransition& operator=(const AnimationStateTransition&);

    AnimationStateTransition(AnimationStateTransition&&) noexcept;
    AnimationStateTransition& operator=(AnimationStateTransition&&) noexcept;

    AnimationState* getFromState() const { return m_fromState; }
    AnimationState* getToState() const { return m_toState; }
    bool canTransition() const { return m_condition(); }

  private:
    AnimationState* m_fromState;
    AnimationState* m_toState;
    std::function<bool()> m_condition;
  };
}