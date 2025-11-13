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
  class Blackboard;
  class EightDirectionsSpriteSheetAnimationDescription;

  class EightDirectionsSpriteSheetAnimation : public Animation
  {
  public:
    EightDirectionsSpriteSheetAnimation(
      const EightDirectionsSpriteSheetAnimationDescription& description,
      const Blackboard& blackboard,
      const sf::Texture& texture
    );
    virtual ~EightDirectionsSpriteSheetAnimation();

    sf::Vector2i getFrameSize() const { return m_frameSize; }
    void updateSpeedModifier();
    void updateDirectionAngle();

    virtual void prepareSprite(Sprite& sprite) override;
    virtual void reset() override;
    virtual void play() override;
    virtual void stop() override;
    virtual void update(float deltaTime) override;

  private:
    const EightDirectionsSpriteSheetAnimationDescription* m_description;
    const sf::Texture* m_texture;
    const Blackboard* m_blackboard;
    sf::Sprite* m_sprite;
    sf::Vector2i m_frameSize;
    UInt32 m_currentFrame;
    Int32 m_currentRectX;
    Int32 m_currentRectY;
    float m_currentTime;
    float m_timePerFrame;

    UInt32 getSpriteSheetColumnFromAngle(sf::Angle angle) const;
    sf::IntRect calculateTextureRect() const;
    void updateCurrentRectX();

    void assertSpriteIsNotNull() const;
  };
}