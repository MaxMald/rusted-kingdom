#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkBlackboard.h"

namespace sf
{
  class Sprite;
}

using sf::Sprite;

namespace rk
{
  class AnimationState;

  class AnimationStateMachine : public NonCopyable
  {
  public:
    AnimationStateMachine(const String& initialStateKey);
    ~AnimationStateMachine();

    const AnimationState* getCurrentState() const { return m_currentState; }
    Blackboard& getBlackboard() { return m_blackboard; }
    const Blackboard& getBlackboard() const { return m_blackboard; }
    void addState(UniquePtr<AnimationState> state);
    void update(float deltaTime, Sprite& sprite);

  private:
    String m_initialStateKey;
    AnimationState* m_currentState;
    Vector<UniquePtr<AnimationState>> m_states;
    Blackboard m_blackboard;

    AnimationState* getStateByKey(const String& stateKey) const;
  };
}