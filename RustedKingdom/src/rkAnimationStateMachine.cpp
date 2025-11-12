#include "rkAnimationStateMachine.h"
#include "rkAnimationState.h"
#include "rkAnimationStateTransition.h"

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

  bool AnimationStateMachine::hasFloat(const String& key) const
  {
    return m_floatParameters.find(key) != m_floatParameters.end();
  }

  void AnimationStateMachine::addFloat(const String& key, float initialValue)
  {
    m_floatParameters[key] = initialValue;
  }

  void AnimationStateMachine::setFloat(const String& key, float value)
  {
    auto it = m_floatParameters.find(key);
    if (it != m_floatParameters.end())
      it->second = value;
  }

  float AnimationStateMachine::getFloat(const String& key) const
  {
    auto it = m_floatParameters.find(key);
    if (it != m_floatParameters.end())
      return it->second;
    return 0.0f;
  }

  bool AnimationStateMachine::hasBool(const String& key) const
  {
    return m_boolParameters.find(key) != m_boolParameters.end();
  }

  void AnimationStateMachine::addBool(const String& key, bool initialValue)
  {
    m_boolParameters[key] = initialValue;
  }

  void AnimationStateMachine::setBool(const String& key, bool value)
  {
    auto it = m_boolParameters.find(key);
    if (it != m_boolParameters.end())
      it->second = value;
  }

  bool AnimationStateMachine::getBool(const String& key) const
  {
    auto it = m_boolParameters.find(key);
    if (it != m_boolParameters.end())
      return it->second;
    return false;
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

  void AnimationStateMachine::update(float deltaTime, Sprite& sprite)
  {
    if (!m_currentState)
      return;

    for (const auto& transition : m_currentState->getTransitions())
    {
      if (transition->canTransition(*this))
      {
        m_currentState->onExit();
        m_currentState = transition->getToState();
        m_currentState->onEnter(sprite);
        break;
      }
    }
    
    m_currentState->update(deltaTime);
  }
}