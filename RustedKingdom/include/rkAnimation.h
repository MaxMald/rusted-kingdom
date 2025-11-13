#pragma once

#include "rkAnimationType.h"
#include "rkNonCopyable.h"

namespace sf
{
  class Sprite;
}

using sf::Sprite;

namespace rk
{
  class Animation : public NonCopyable
  {
  public:
    Animation(const String& animationKey, animationType::Type type);
    virtual ~Animation();

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

  private:
    animationType::Type m_type;
    String m_animationKey;
  };
}