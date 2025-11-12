#pragma once

#include "rkPrerequisites.h"

namespace sf
{
  class Sprite;
}

using sf::Sprite;

namespace rk
{
  class Animation;
  class AnimationStateTransition;

  class AnimationState
  {
  public:
    AnimationState(Animation& animation);
    ~AnimationState();

    Animation& getAnimation();
    const Animation& getAnimation() const;
    bool isActive() const { return m_isActive; }
    const Vector<const AnimationStateTransition*>& getTransitions() const { return m_transitions; }

    /**
     * @brief Adds a transition to this animation state. Ownership of the
     * transition is transferred to the state.
     * 
     * @param transition The transition to add.
     */
    void addTransition(const AnimationStateTransition* transition);

    void onEnter(Sprite& sprite);
    void update(float deltaTime);
    void onExit();

  private:
    bool m_isActive;
    Animation* m_animation;
    Vector<const AnimationStateTransition*> m_transitions;
  };
}