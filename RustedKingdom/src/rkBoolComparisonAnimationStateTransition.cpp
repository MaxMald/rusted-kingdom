#include "rkBoolComparisonAnimationStateTransition.h"
#include "rkAnimationStateMachine.h"
#include "rkBlackboard.h"
#include "rkBlackboardValueGroup.h"

namespace rk
{
  BoolComparisonAnimationStateTransition::BoolComparisonAnimationStateTransition(
    AnimationState& fromState,
    AnimationState& toState,
    bool expectedValue,
    const String& boolKey
  ) :
    AnimationStateTransition(fromState, toState),
    m_expectedValue(expectedValue),
    m_boolKey(boolKey)
  {
  }

  BoolComparisonAnimationStateTransition::~BoolComparisonAnimationStateTransition()
  {
  }

  bool BoolComparisonAnimationStateTransition::canTransition(
    const AnimationStateMachine& stateMachine
  ) const
  {
    const BlackboardValueGroup<bool>& boolGroup =
      stateMachine.getBlackboard().getBoolValues();

    if (!boolGroup.hasValue(m_boolKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "Bool parameter with key '%s' does not exist in the AnimationStateMachine.",
          m_boolKey.c_str()
        )
      );
    }

    return boolGroup.getValue(m_boolKey) == m_expectedValue;
  }
}