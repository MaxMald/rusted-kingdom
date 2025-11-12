#pragma once

#include "rkAnimationType.h"

namespace sf
{
  class Sprite;
}

using sf::Sprite;

namespace rk
{
  class AnimationStateMachine;

  class Animation
  {
  public:
    Animation(
      const AnimationStateMachine& animationStateMachine,
      const String& animationKey,
      animationType::Type type
    );
    ~Animation();

    Animation(const Animation&) = delete;
    Animation& operator=(const Animation&) = delete;

    Animation(Animation&&) = delete;
    Animation& operator=(Animation&&) = delete;

    animationType::Type getType() const { return m_type; }
    const String& getAnimationKey() const { return m_animationKey; }
    bool isPlaying() const { return m_isPlaying; }

    virtual void prepareSprite(Sprite& sprite) = 0;
    virtual void reset() = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void update(float deltaTime) = 0;

  protected:
    bool m_isPlaying;
    const AnimationStateMachine* m_animationStateMachine;

  private:
    animationType::Type m_type;
    String m_animationKey;
  };
}