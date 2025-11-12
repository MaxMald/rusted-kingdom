#pragma once

#include <functional>
#include "rkPrerequisites.h"
#include "rkLogicalComparisonType.h"

namespace rk
{
  class AnimationStateMachine;
  class AnimationState;
  class Animation;

  class AnimationStateMachineBuilder
  {
  public:

    AnimationStateMachineBuilder();
    ~AnimationStateMachineBuilder();

    AnimationStateMachineBuilder(const AnimationStateMachineBuilder& other) = delete;
    AnimationStateMachineBuilder& operator=(const AnimationStateMachineBuilder& other) = delete;

    AnimationStateMachineBuilder(AnimationStateMachineBuilder&& other) noexcept = delete;
    AnimationStateMachineBuilder& operator=(AnimationStateMachineBuilder&& other) noexcept = delete;

    AnimationStateMachineBuilder& createStateMachine();
    AnimationStateMachine* build();

    AnimationStateMachineBuilder& withFloat(const String& floatKey, float initialValue);
    AnimationStateMachineBuilder& withBool(const String& boolKey, bool initialValue);

    AnimationStateMachineBuilder& withAnimationState(
      const String& stateKey,
      Animation& animation
    );

    AnimationStateMachineBuilder& withBoolComparisonTransition(
      const String& toStateKey,
      const String& boolKey,
      bool expectedValue
    );

    AnimationStateMachineBuilder& withFloatComparisonTransition(
      const String& toStateKey,
      float leftValue,
      logicalComparisonType::Type comparisonType,
      const String& rightValueFloatKey
    );

  private:
    AnimationStateMachine* m_currentAnimationStateMachine;
    AnimationState* m_currentAnimationState;
    UnorderedMap<String, AnimationState*> m_statesMap;

    AnimationState* getAnimationState(const String& stateKey) const;

    void assertCurrentAnimationStateMachineNotNull() const;
    void assertCurrentAnimationStateNotNull() const;
    void assertDoesNotHaveState(const String& stateKey) const;
  };
}
