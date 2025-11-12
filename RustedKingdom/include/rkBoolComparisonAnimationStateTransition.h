#pragma once

#include "rkAnimationStateTransition.h"

namespace rk
{
  class BoolComparisonAnimationStateTransition : public AnimationStateTransition
  {
  public:
    BoolComparisonAnimationStateTransition(
      AnimationState* fromState,
      AnimationState* toState,
      bool expectedValue,
      const String& boolKey
    );
    virtual ~BoolComparisonAnimationStateTransition();

    BoolComparisonAnimationStateTransition(const BoolComparisonAnimationStateTransition&);
    BoolComparisonAnimationStateTransition& operator=(const BoolComparisonAnimationStateTransition&);

    BoolComparisonAnimationStateTransition(BoolComparisonAnimationStateTransition&&) noexcept;
    BoolComparisonAnimationStateTransition& operator=(BoolComparisonAnimationStateTransition&&) noexcept;

    bool canTransition(const AnimationStateMachine& stateMachine) const override;

  private:
    String m_boolKey;
    bool m_expectedValue;
  };
}