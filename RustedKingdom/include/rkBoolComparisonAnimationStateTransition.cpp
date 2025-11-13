#include "rkBoolComparisonAnimationStateTransition.h"
#include "rkAnimationStateMachine.h"
#include "rkBlackboard.h"
#include "rkBlackboardValueGroup.h"

namespace rk
{
  BoolComparisonAnimationStateTransition::BoolComparisonAnimationStateTransition(
    AnimationState* fromState,
    AnimationState* toState,
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

  BoolComparisonAnimationStateTransition::BoolComparisonAnimationStateTransition(
    const BoolComparisonAnimationStateTransition& other
  ) :
    AnimationStateTransition(other),
    m_expectedValue(other.m_expectedValue),
    m_boolKey(other.m_boolKey)
  {
  }

  BoolComparisonAnimationStateTransition& BoolComparisonAnimationStateTransition::operator=(
    const BoolComparisonAnimationStateTransition& other
    )
  {
    if (this != &other)
    {
      AnimationStateTransition::operator=(other);
      m_expectedValue = other.m_expectedValue;
      m_boolKey = other.m_boolKey;
    }
    return *this;
  }

  BoolComparisonAnimationStateTransition::BoolComparisonAnimationStateTransition(
    BoolComparisonAnimationStateTransition&& other
  ) noexcept :
    AnimationStateTransition(std::move(other)),
    m_expectedValue(other.m_expectedValue),
    m_boolKey(std::move(other.m_boolKey))
  {
    other.m_expectedValue = false;
    other.m_boolKey.clear();
  }

  BoolComparisonAnimationStateTransition& BoolComparisonAnimationStateTransition::operator=(
    BoolComparisonAnimationStateTransition&& other
  ) noexcept
  {
    if (this != &other)
    {
      AnimationStateTransition::operator=(std::move(other));
      m_expectedValue = other.m_expectedValue;
      m_boolKey = std::move(other.m_boolKey);
      other.m_expectedValue = false;
      other.m_boolKey.clear();
    }
    return *this;
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