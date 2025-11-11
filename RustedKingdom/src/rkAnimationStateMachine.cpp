#include "rkAnimationStateMachine.h"
#include "rkAnimationState.h"

namespace rk
{
  AnimationStateMachine::AnimationStateMachine() :
    m_currentState(nullptr),
    m_states()
  {
  }

  AnimationStateMachine::~AnimationStateMachine()
  {
    for (auto state : m_states)
      delete state;
    m_states.clear();
  }

  void AnimationStateMachine::addState(AnimationState* state)
  {
    m_states.push_back(state);
    if (m_currentState == nullptr)
    {
      m_currentState = state;
      m_currentState->onEnter();
    }
  }
  void AnimationStateMachine::update(float deltaTime)
  {
    if (!m_currentState)
      return;

    for (const auto& transition : m_currentState->getTransitions())
    {
      if (transition.canTransition())
      {
        m_currentState->onExit();
        m_currentState = transition.getToState();
        m_currentState->onEnter();
        break;
      }
    }
    
    m_currentState->update(deltaTime);
  }
}