#pragma once

#include "rkAnimationStateTransition.h"

namespace rk
{
  class Animation;

  class AnimationState
  {
  public:
    AnimationState(Animation& animation);
    ~AnimationState();

    Animation& getAnimation();
    const Animation& getAnimation() const;
    bool isActive() const { return m_isActive; }
    const Vector<AnimationStateTransition>& getTransitions() const { return m_transitions; }

    void addTransition(const AnimationStateTransition& transition);
    void onEnter();
    void update(float deltaTime);
    void onExit();

  private:
    bool m_isActive;
    Animation* m_animation;
    Vector<AnimationStateTransition> m_transitions;
  };
}