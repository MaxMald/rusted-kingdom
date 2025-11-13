#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace sf
{
  class Sprite;
}

using sf::Sprite;

namespace rk
{
  class Blackboard;
  class Animation;
  class AnimationStateTransition;

  class AnimationState : public NonCopyable
  {
  public:
    AnimationState(const String& key, UniquePtr<Animation> animation);
    ~AnimationState();

    Animation& getAnimation() { return *m_animation; }
    const Animation& getAnimation() const { return *m_animation; }
    const String& getKey() const { return m_key; }
    const Vector<UniquePtr<AnimationStateTransition>>& getTransitions() const { return m_transitions; }

    void addTransition(UniquePtr<AnimationStateTransition> transition);
    void onEnter(Sprite& sprite);
    void update(float deltaTime);
    void onExit();

  private:
    String m_key;
    UniquePtr<Animation> m_animation;
    Vector<UniquePtr<AnimationStateTransition>> m_transitions;
  };
}