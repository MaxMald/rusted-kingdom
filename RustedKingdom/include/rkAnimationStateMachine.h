#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class AnimationState;

  class AnimationStateMachine
  {
  public:
    AnimationStateMachine();
    ~AnimationStateMachine();

    AnimationState* getCurrentState() const { return m_currentState; }

    void addState(AnimationState* state);
    void update(float deltaTime);

  private:
    AnimationState* m_currentState;
    Vector<AnimationState*> m_states;
  };
}