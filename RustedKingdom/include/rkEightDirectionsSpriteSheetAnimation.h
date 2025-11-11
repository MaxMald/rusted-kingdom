#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Angle.hpp>

#include "rkEightDirectionsSpriteSheetAnimationDescription.h"

namespace sf
{
  class Texture;
  class Sprite;
}

namespace rk
{
  class EightDirectionsSpriteSheetAnimationDescription;

  class EightDirectionsSpriteSheetAnimation
  {
  public:
    EightDirectionsSpriteSheetAnimation(
      const EightDirectionsSpriteSheetAnimationDescription& description,
      const sf::Texture& texture,
      sf::Sprite& sprite
    );
    ~EightDirectionsSpriteSheetAnimation();

    sf::Vector2i getFrameSize() const { return m_frameSize; }

    bool isPlaying() const { return m_isPlaying; }
    void reset();
    void play();
    void stop();
    void update(float deltaTime);
    void setSpeedModifier(float speedModifier);
    void setDirectionAngle(sf::Angle angle);

  private:
    const EightDirectionsSpriteSheetAnimationDescription* m_description;
    const sf::Texture* m_texture;
    sf::Sprite* m_sprite;
    sf::Vector2i m_frameSize;
    UInt32 m_currentFrame;
    Int32 m_currentRectX;
    Int32 m_currentRectY;
    float m_currentTime;
    float m_timePerFrame;
    bool m_isPlaying;

    UInt32 getSpriteSheetColumnFromAngle(sf::Angle angle) const;
    sf::IntRect calculateTextureRect() const;
  };
}