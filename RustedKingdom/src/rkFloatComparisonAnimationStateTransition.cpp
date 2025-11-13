#include "rkFloatComparisonAnimationStateTransition.h"

#include <utility>

#include "rkAnimationStateMachine.h"
#include "rkLogicalComparisonUtilities.h"
#include "rkBlackboard.h"
#include "rkBlackboardValueGroup.h"

namespace rk
{
  FloatComparisonAnimationStateTransition::FloatComparisonAnimationStateTransition(
    AnimationState& fromState,
    AnimationState& toState,
    float leftValue,
    logicalComparisonType::Type comparisonType,
    const String& rightValueFloatKey
  ) : 
    AnimationStateTransition(fromState, toState),
    m_leftValue(leftValue),
    m_comparisonType(comparisonType),
    m_rightValueFloatKey(rightValueFloatKey)
  {
  }

  FloatComparisonAnimationStateTransition::~FloatComparisonAnimationStateTransition()
  {
  }

  bool FloatComparisonAnimationStateTransition::canTransition(
    const AnimationStateMachine& stateMachine
  ) const
  {
    const BlackboardValueGroup<float>& floatGroup =
      stateMachine.getBlackboard().getFloatValues();

    if (!floatGroup.hasValue(m_rightValueFloatKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "FloatComparisonAnimationStateTransition::canTransition: "
          "Float parameter '%s' does not exist in the AnimationStateMachine.",
          m_rightValueFloatKey.c_str()
        )
      );
    }

    float rightValue = floatGroup.getValue(m_rightValueFloatKey);
    return logicalComparisonUtilities::evaluateFloatComparison(
      m_leftValue,
      rightValue,
      m_comparisonType
    );
  }
}