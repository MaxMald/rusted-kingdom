#include "rkFloatComparisonAnimationStateTransition.h"

#include <utility>

#include "rkAnimationStateMachine.h"
#include "rkLogicalComparisonUtilities.h"
#include "rkBlackboard.h"
#include "rkBlackboardValueGroup.h"

namespace rk
{
  FloatComparisonAnimationStateTransition::FloatComparisonAnimationStateTransition(
    AnimationState* fromState,
    AnimationState* toState,
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

  FloatComparisonAnimationStateTransition::FloatComparisonAnimationStateTransition(
    const FloatComparisonAnimationStateTransition& other
  ) :
    AnimationStateTransition(other),
    m_leftValue(other.m_leftValue),
    m_comparisonType(other.m_comparisonType),
    m_rightValueFloatKey(other.m_rightValueFloatKey)
  {
  }

  FloatComparisonAnimationStateTransition& FloatComparisonAnimationStateTransition::operator=(
    const FloatComparisonAnimationStateTransition& other
  )
  {
    if (this != &other)
    {
      AnimationStateTransition::operator=(other);
      m_leftValue = other.m_leftValue;
      m_comparisonType = other.m_comparisonType;
      m_rightValueFloatKey = other.m_rightValueFloatKey;
    }

    return *this;
  }

  FloatComparisonAnimationStateTransition::FloatComparisonAnimationStateTransition(
    FloatComparisonAnimationStateTransition&& other
  ) noexcept :
    AnimationStateTransition(std::move(other)),
    m_leftValue(std::move(other.m_leftValue)),
    m_comparisonType(other.m_comparisonType),
    m_rightValueFloatKey(std::move(other.m_rightValueFloatKey))
  {
    other.m_leftValue = 0.0f;
    other.m_comparisonType = logicalComparisonType::Type::Undefined;
  }

  FloatComparisonAnimationStateTransition& FloatComparisonAnimationStateTransition::operator=(
    FloatComparisonAnimationStateTransition&& other
  ) noexcept
  {
    if (this != &other)
    {
      AnimationStateTransition::operator=(std::move(other));
      m_leftValue = std::move(other.m_leftValue);
      m_comparisonType = other.m_comparisonType;
      m_rightValueFloatKey = std::move(other.m_rightValueFloatKey);

      other.m_leftValue = 0.0f;
      other.m_comparisonType = logicalComparisonType::Type::Undefined;
    }

    return *this;
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