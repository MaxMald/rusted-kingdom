#pragma once

#include "rkAnimationStateTransition.h"
#include "rkLogicalComparisonType.h"

namespace rk
{
  class FloatComparisonAnimationStateTransition : public AnimationStateTransition
  {
  public:
    FloatComparisonAnimationStateTransition(
      AnimationState& fromState,
      AnimationState& toState,
      float leftValue,
      logicalComparisonType::Type comparisonType,
      const String& rightValueFloatKey
    );
    virtual ~FloatComparisonAnimationStateTransition();

    bool canTransition(const AnimationStateMachine&) const override;

  private:
    String m_rightValueFloatKey;
    float m_leftValue;
    logicalComparisonType::Type m_comparisonType;
  };
}