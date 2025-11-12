#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Angle.hpp>

#include "rkAnimation.h"
#include "rkEightDirectionsSpriteSheetAnimationDescription.h"

namespace sf
{
  class Texture;
}

using sf::Texture;

namespace rk
{
  class EightDirectionsSpriteSheetAnimationDescription;

  class EightDirectionsSpriteSheetAnimation : public Animation
  {
  public:

    EightDirectionsSpriteSheetAnimation(
      const AnimationStateMachine& animationStateMachine,
      const EightDirectionsSpriteSheetAnimationDescription& description,
      const sf::Texture& texture
    );
    ~EightDirectionsSpriteSheetAnimation();

    sf::Vector2i getFrameSize() const { return m_frameSize; }
    void setSpeedModifier(float speedModifier);
    void setDirectionAngle(sf::Angle angle);

    virtual void prepareSprite(Sprite& sprite) override;
    virtual void reset() override;
    virtual void play() override;
    virtual void stop() override;
    virtual void update(float deltaTime) override;

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

    UInt32 getSpriteSheetColumnFromAngle(sf::Angle angle) const;
    sf::IntRect calculateTextureRect() const;

    void assertSpriteIsNotNull() const;
  };
}