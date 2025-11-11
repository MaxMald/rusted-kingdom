#include "rkEightDirectionsSpriteSheetAnimation.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "rkAssertions.h"

namespace rk
{
  namespace { 
    constexpr float PiOver2 = 1.5707f;
    constexpr float PiOver16 = 0.19635f;
    constexpr float TwoPi = 6.28318f;
    constexpr float EightDirectionsAnimationAngleToColumn = 8.0f / TwoPi;
    constexpr sf::Angle AngleOffset = sf::radians(PiOver2 + PiOver16);
  }

  EightDirectionsSpriteSheetAnimation::EightDirectionsSpriteSheetAnimation(
    const EightDirectionsSpriteSheetAnimationDescription& description,
    const sf::Texture& texture,
    sf::Sprite& sprite
  ) :
    m_description(&description),
    m_texture(&texture),
    m_sprite(&sprite),
    m_frameSize(
      static_cast<Int32>(description.getFrameWidth()),
      static_cast<Int32>(description.getFrameHeight())
    ),
    m_currentFrame(0),
    m_currentRectX(0),
    m_currentRectY(0),
    m_currentTime(0.0f),
    m_timePerFrame(1.0f / description.getFramesPerSecond()),
    m_isPlaying(false)
  {
  }

  EightDirectionsSpriteSheetAnimation::~EightDirectionsSpriteSheetAnimation()
  {
  }

  void EightDirectionsSpriteSheetAnimation::reset()
  {
    m_currentFrame = 0;
    m_currentTime = 0.0f;
    m_timePerFrame = 1.0f / m_description->getFramesPerSecond();
  }

  void EightDirectionsSpriteSheetAnimation::play()
  {
    if (m_isPlaying)
      return;

    assertions::assertNotNull(m_texture, "animation texture");
    m_sprite->setTexture(*m_texture);
    m_isPlaying = true;
  }

  void EightDirectionsSpriteSheetAnimation::stop()
  {
    if (!m_isPlaying)
      return;

    m_isPlaying = false;
  }

  void EightDirectionsSpriteSheetAnimation::update(float deltaTime)
  {
    if (!m_isPlaying)
      return;

    m_currentTime += deltaTime;
    while (m_currentTime >= m_timePerFrame)
    {
      m_currentTime -= m_timePerFrame;
      m_currentFrame = (m_currentFrame + 1) % m_description->getAnimationLength();
      m_currentRectX = m_currentFrame * m_description->getFrameWidth();
    }

    m_sprite->setTextureRect(calculateTextureRect());
  }

  void EightDirectionsSpriteSheetAnimation::setSpeedModifier(float speedModifier)
  {
    if (speedModifier == 0.0f)
    {
      m_timePerFrame = 0;
    } 
    else
    {
      m_timePerFrame = 1.0f / (m_description->getFramesPerSecond() * speedModifier);
    }
  }

  void EightDirectionsSpriteSheetAnimation::setDirectionAngle(sf::Angle angle)
  {
    UInt32 spriteSheetColumn = getSpriteSheetColumnFromAngle(angle);
    m_currentRectY = spriteSheetColumn * m_description->getFrameHeight();
  }

  UInt32 EightDirectionsSpriteSheetAnimation::getSpriteSheetColumnFromAngle(
    sf::Angle angle
  ) const
  {
    float finalAngleAsRadians = (angle + AngleOffset).asRadians();
    float desiredRow = finalAngleAsRadians * EightDirectionsAnimationAngleToColumn;
    return static_cast<UInt32>(desiredRow) % 8;
  }

  sf::IntRect EightDirectionsSpriteSheetAnimation::calculateTextureRect() const
  {
    return sf::IntRect(
      sf::Vector2i(m_currentRectX, m_currentRectY),
      m_frameSize
    );
  }
}