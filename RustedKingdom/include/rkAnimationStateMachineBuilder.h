#pragma once

#include <functional>

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkLogicalComparisonType.h"

namespace sf
{
  class Texture;
  class Angle;
}

using sf::Texture;
using sf::Angle;
using sf::Vector2f;

namespace rk
{
  class AnimationFactory;
  class AnimationStateMachine;
  class AnimationState;
  class Animation;
  class EightDirectionsSpriteSheetAnimationDescription;

  class AnimationStateMachineBuilder : public NonCopyable
  {
  public:

    AnimationStateMachineBuilder(AnimationFactory& animationFactory);
    ~AnimationStateMachineBuilder();

    AnimationStateMachineBuilder& createStateMachine(const String& initialStateKey);
    UniquePtr<AnimationStateMachine> build();

    AnimationStateMachineBuilder& withFloat(const String& floatKey, float initialValue);
    AnimationStateMachineBuilder& withBool(const String& boolKey, bool initialValue);
    AnimationStateMachineBuilder& withAngle(const String& angleKey, Angle initialValue);
    AnimationStateMachineBuilder& withVector2f(const String& vectorKey, Vector2f initialValue);

    AnimationStateMachineBuilder& withAnimationState(
      const String& stateKey,
      UniquePtr<Animation> animation
    );

    AnimationStateMachineBuilder& withEightDirectionAnimationState(
      const String& stateKey,
      const String& descriptionKey
    );

    AnimationStateMachineBuilder& withBoolComparisonTransition(
      const String& fromStateKey,
      const String& toStateKey,
      const String& boolKey,
      bool expectedValue
    );

    AnimationStateMachineBuilder& withFloatComparisonTransition(
      const String& fromStateKey,
      const String& toStateKey,
      float leftValue,
      logicalComparisonType::Type comparisonType,
      const String& rightValueFloatKey
    );

  private:
    AnimationStateMachine* m_currentAnimationStateMachine;
    UnorderedMap<String, AnimationState*> m_statesMap;
    AnimationFactory& m_animationFactory;

    AnimationState* getAnimationState(const String& stateKey) const;

    void assertCurrentAnimationStateMachineNotNull() const;
    void assertDoesNotHaveState(const String& stateKey) const;
  };
}
