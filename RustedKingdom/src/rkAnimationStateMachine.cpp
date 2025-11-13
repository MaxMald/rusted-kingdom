#include "rkAnimationStateMachine.h"
#include "rkAnimationState.h"
#include "rkAnimationStateTransition.h"

namespace rk
{
  AnimationStateMachine::AnimationStateMachine(const String& initialStateKey) :
    m_initialStateKey(initialStateKey),
    m_currentState(nullptr),
    m_states()
  {
  }

  AnimationStateMachine::~AnimationStateMachine()
  {
    m_currentState = nullptr;
    m_states.clear();
  }

  void AnimationStateMachine::addState(UniquePtr<AnimationState> state)
  {
    m_states.push_back(std::move(state));
  }

  void AnimationStateMachine::update(float deltaTime, Sprite& sprite)
  {
    if (!m_currentState)
    {
      m_currentState = getStateByKey(m_initialStateKey);
      m_currentState->onEnter(sprite);
    }

    for (const auto& transition : m_currentState->getTransitions())
    {
      if (transition->canTransition(*this))
      {
        m_currentState->onExit();
        m_currentState = &(transition->getToState());
        m_currentState->onEnter(sprite);
        break;
      }
    }
    
    m_currentState->update(deltaTime);
  }

  AnimationState* AnimationStateMachine::getStateByKey(
    const String& stateKey
  ) const
  {
    for (const auto& state : m_states)
    {
      if (state->getKey() == stateKey)
        return state.get();
    }

    throw RuntimeErrorException(
      String::Format(
        "AnimationStateMachine::getStateByKey: State '%s' does not exist.",
        stateKey.c_str()
      )
    );
  }
}