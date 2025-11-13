#include "rkAnimationStateMachineBuilder.h"
#include "rkAnimationStateMachine.h"
#include "rkAnimationState.h"
#include "rkEightDirectionsSpriteSheetAnimation.h"
#include "rkAnimationStateTransition.h"
#include "rkBoolComparisonAnimationStateTransition.h"
#include "rkFloatComparisonAnimationStateTransition.h"
#include "rkBlackboard.h"
#include "rkAnimationFactory.h"

namespace rk
{
  AnimationStateMachineBuilder::AnimationStateMachineBuilder(
    AnimationFactory& animationFactory
  ) :
    m_currentAnimationStateMachine(nullptr),
    m_statesMap(),
    m_animationFactory(animationFactory)
  {
  }

  AnimationStateMachineBuilder::~AnimationStateMachineBuilder()
  {
    if (m_currentAnimationStateMachine)
      delete m_currentAnimationStateMachine;
    m_currentAnimationStateMachine = nullptr;
    m_statesMap.clear();
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::createStateMachine(
    const String& initialStateKey
  )
  {
    if (m_currentAnimationStateMachine)
    {
      throw RuntimeErrorException(
        "AnimationStateMachineBuilder::createStateMachine: A state machine is already being built."
      );
    }

    m_currentAnimationStateMachine = new AnimationStateMachine(initialStateKey);
    return *this;
  }

  UniquePtr<AnimationStateMachine> AnimationStateMachineBuilder::build()
  {
    assertCurrentAnimationStateMachineNotNull();

    AnimationStateMachine* builtStateMachine = m_currentAnimationStateMachine;

    m_currentAnimationStateMachine = nullptr;
    m_statesMap.clear();

    return UniquePtr<AnimationStateMachine>(builtStateMachine);
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withFloat(
    const String& floatKey,
    float initialValue)
  {
    assertCurrentAnimationStateMachineNotNull();

    BlackboardValueGroup<float>& floatValueGroup =
      m_currentAnimationStateMachine->getBlackboard().getFloatValues();

    if (floatValueGroup.hasValue(floatKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "AnimationStateMachineBuilder::withFloat: A float parameter with key '%s' already exists.",
          floatKey.c_str()
        )
      );
    }

    floatValueGroup.setValue(floatKey, initialValue);
    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withBool(
    const String& boolKey,
    bool initialValue)
  {
    assertCurrentAnimationStateMachineNotNull();

    BlackboardValueGroup<Bool>& boolValueGroup =
      m_currentAnimationStateMachine->getBlackboard().getBoolValues();

    if (boolValueGroup.hasValue(boolKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "AnimationStateMachineBuilder::withBool: A bool parameter with key '%s' already exists.",
          boolKey.c_str()
        )
      );
    }

    boolValueGroup.setValue(boolKey, initialValue);
    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withAngle(
    const String& angleKey,
    Angle initialValue
  )
  {
    assertCurrentAnimationStateMachineNotNull();

    BlackboardValueGroup<Angle>& angleValueGroup =
      m_currentAnimationStateMachine->getBlackboard().getAngleValues();

    if (angleValueGroup.hasValue(angleKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "AnimationStateMachineBuilder::withAngle: An angle parameter with key '%s' already exists.",
          angleKey.c_str()
        )
      );
    }

    angleValueGroup.setValue(angleKey, initialValue);
    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withVector2f(
    const String& vectorKey,
    Vector2f initialValue
  )
  {
    assertCurrentAnimationStateMachineNotNull();

    BlackboardValueGroup<Vector2f>& vector2fValueGroup =
      m_currentAnimationStateMachine->getBlackboard().getVector2fValues();

    if (vector2fValueGroup.hasValue(vectorKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "AnimationStateMachineBuilder::withVector2f: A Vector2f parameter with key '%s' already exists.",
          vectorKey.c_str()
        )
      );
    }

    vector2fValueGroup.setValue(vectorKey, initialValue);
    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withAnimationState(
    const String& stateKey,
    UniquePtr<Animation> animation
  )
  {
    assertCurrentAnimationStateMachineNotNull();
    assertDoesNotHaveState(stateKey);

    UniquePtr<AnimationState> newState = MakeUnique<AnimationState>(
      stateKey,
      std::move(animation)
    );

    m_statesMap[stateKey] = newState.get();
    m_currentAnimationStateMachine->addState(std::move(newState));

    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withEightDirectionAnimationState(
    const String& stateKey,
    const String& descriptionKey
  )
  {
    assertCurrentAnimationStateMachineNotNull();
    assertDoesNotHaveState(stateKey);

    UniquePtr<Animation> newAnimation = m_animationFactory
      .createEightDirectionsAnimation(
        descriptionKey,
        m_currentAnimationStateMachine->getBlackboard()
      );

    UniquePtr<AnimationState> newState = MakeUnique<AnimationState>(
      stateKey,
      std::move(newAnimation)
    );

    m_statesMap[stateKey] = newState.get();
    m_currentAnimationStateMachine->addState(std::move(newState));
    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withBoolComparisonTransition(
    const String& fromStateKey,
    const String& toStateKey,
    const String& boolKey,
    bool expectedValue
  )
  {
    assertCurrentAnimationStateMachineNotNull();

    AnimationState* fromAnimationState = getAnimationState(fromStateKey);
    UniquePtr<AnimationStateTransition> transition = MakeUnique<BoolComparisonAnimationStateTransition>(
      *fromAnimationState,
      *getAnimationState(toStateKey),
      expectedValue,
      boolKey
    );

    fromAnimationState->addTransition(std::move(transition));
    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withFloatComparisonTransition(
    const String& fromStateKey,
    const String& toStateKey,
    float leftValue,
    logicalComparisonType::Type comparisonType,
    const String& rightValueFloatKey
  )
  {
    assertCurrentAnimationStateMachineNotNull();

    AnimationState* fromAnimationState = getAnimationState(fromStateKey);
    UniquePtr<AnimationStateTransition> transition = MakeUnique<FloatComparisonAnimationStateTransition>(
      *fromAnimationState,
      *getAnimationState(toStateKey),
      leftValue,
      comparisonType,
      rightValueFloatKey
    );

    fromAnimationState->addTransition(std::move(transition));
    return *this;
  }

  AnimationState* AnimationStateMachineBuilder::getAnimationState(
    const String& stateKey
  ) const
  {
    auto it = m_statesMap.find(stateKey);
    if (it != m_statesMap.end())
      return it->second;

    throw RuntimeErrorException(
      String::Format(
        "AnimationStateMachineBuilder::getAnimationState: State '%s' does not exist.",
        stateKey.c_str()
      )
    );
  }

  void AnimationStateMachineBuilder::assertCurrentAnimationStateMachineNotNull() const
  {
    if (m_currentAnimationStateMachine == nullptr)
    {
      throw RuntimeErrorException(
        "AnimationStateMachineBuilder: No state machine is being built."
      );
    }
  }

  void AnimationStateMachineBuilder::assertDoesNotHaveState(
    const String& stateKey
  ) const
  {
    if (m_statesMap.find(stateKey) != m_statesMap.end())
    {
      throw RuntimeErrorException(
        String::Format(
          "AnimationStateMachineBuilder::assertDoesNotHaveState: State '%s' already exists.",
          stateKey.c_str()
        )
      );
    }
  }
}