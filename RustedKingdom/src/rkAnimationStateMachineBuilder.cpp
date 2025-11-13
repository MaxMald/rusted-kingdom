#include "rkAnimationStateMachineBuilder.h"
#include "rkAnimationStateMachine.h"
#include "rkAnimationState.h"
#include "rkEightDirectionsSpriteSheetAnimation.h"
#include "rkAnimationStateTransition.h"
#include "rkBoolComparisonAnimationStateTransition.h"
#include "rkFloatComparisonAnimationStateTransition.h"
#include "rkBlackboard.h"

namespace rk
{
  AnimationStateMachineBuilder::AnimationStateMachineBuilder()
    : m_currentAnimationStateMachine(nullptr)
    , m_currentAnimationState(nullptr)
    , m_statesMap()
  {
  }

  AnimationStateMachineBuilder::~AnimationStateMachineBuilder()
  {
    if (m_currentAnimationStateMachine)
      delete m_currentAnimationStateMachine;
    m_currentAnimationStateMachine = nullptr;
    m_currentAnimationState = nullptr;
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
    m_currentAnimationState = nullptr;
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

    if (!floatValueGroup.hasValue(floatKey))
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

    if (!boolValueGroup.hasValue(boolKey))
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
    m_currentAnimationState = newState.get();
    m_currentAnimationStateMachine->addState(std::move(newState));

    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withEightDirectionAnimationState(
    const String& stateKey,
    const EightDirectionsSpriteSheetAnimationDescription& description,
    const Texture& texture
  )
  {
    assertCurrentAnimationStateMachineNotNull();
    assertDoesNotHaveState(stateKey);

    UniquePtr<Animation> newAnimation = MakeUnique<EightDirectionsSpriteSheetAnimation>(
      description,
      m_currentAnimationStateMachine->getBlackboard(),
      texture
    );

    UniquePtr<AnimationState> newState = MakeUnique<AnimationState>(
      stateKey,
      std::move(newAnimation)
    );

    m_statesMap[stateKey] = newState.get();
    m_currentAnimationState = newState.get();
    m_currentAnimationStateMachine->addState(std::move(newState));
    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withBoolComparisonTransition(
    const String& toStateKey,
    const String& boolKey,
    bool expectedValue
  )
  {
    assertCurrentAnimationStateMachineNotNull();
    assertCurrentAnimationStateNotNull();

    UniquePtr<AnimationStateTransition> transition = MakeUnique<BoolComparisonAnimationStateTransition>(
      m_currentAnimationState,
      getAnimationState(toStateKey),
      expectedValue,
      boolKey
    );

    m_currentAnimationState->addTransition(std::move(transition));
    return *this;
  }

  AnimationStateMachineBuilder& AnimationStateMachineBuilder::withFloatComparisonTransition(
    const String& toStateKey,
    float leftValue,
    logicalComparisonType::Type comparisonType,
    const String& rightValueFloatKey
  )
  {
    assertCurrentAnimationStateMachineNotNull();
    assertCurrentAnimationStateNotNull();

    UniquePtr<AnimationStateTransition> transition = MakeUnique<FloatComparisonAnimationStateTransition>(
      m_currentAnimationState,
      getAnimationState(toStateKey),
      leftValue,
      comparisonType,
      rightValueFloatKey
    );

    m_currentAnimationState->addTransition(std::move(transition));
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

  void AnimationStateMachineBuilder::assertCurrentAnimationStateNotNull() const
  {
    if (m_currentAnimationState == nullptr)
    {
      throw RuntimeErrorException(
        "AnimationStateMachineBuilder: No animation state is currently selected."
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