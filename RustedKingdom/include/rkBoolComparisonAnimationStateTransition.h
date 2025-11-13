#pragma once

#include "rkAnimationStateTransition.h"

namespace rk
{
  class BoolComparisonAnimationStateTransition : public AnimationStateTransition
  {
  public:
    BoolComparisonAnimationStateTransition(
      AnimationState& fromState,
      AnimationState& toState,
      bool expectedValue,
      const String& boolKey
    );
    virtual ~BoolComparisonAnimationStateTransition();

    bool canTransition(const AnimationStateMachine&) const override;

  private:
    String m_boolKey;
    bool m_expectedValue;
  };
}