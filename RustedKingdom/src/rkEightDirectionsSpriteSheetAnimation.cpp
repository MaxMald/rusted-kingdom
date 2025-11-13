#include "rkEightDirectionsSpriteSheetAnimation.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "rkAssertions.h"
#include "rkBlackboard.h"

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
    const Blackboard& blackboard,
    const sf::Texture& texture
  ) :
    Animation(
      description.getAnimationKey(), 
      animationType::Type::eightDirectional
    ),
    m_description(description),
    m_blackboard(blackboard),
    m_texture(texture),
    m_sprite(nullptr),
    m_frameSize(
      static_cast<Int32>(description.getFrameWidth()),
      static_cast<Int32>(description.getFrameHeight())
    ),
    m_currentFrame(0),
    m_currentRectX(0),
    m_currentRectY(0),
    m_currentTime(0.0f),
    m_timePerFrame(1.0f / description.getFramesPerSecond())
  {
  }

  EightDirectionsSpriteSheetAnimation::~EightDirectionsSpriteSheetAnimation()
  {
  }

  void EightDirectionsSpriteSheetAnimation::prepareSprite(Sprite& sprite)
  {
    m_sprite = &sprite;
    m_sprite->setTexture(m_texture);
    m_sprite->setTextureRect(calculateTextureRect());
  }

  void EightDirectionsSpriteSheetAnimation::reset()
  {
    m_currentFrame = m_description.getInitialFrame();
    m_currentTime = 0.0f;

    float framesPerSecond = m_description.getFramesPerSecond();
    if (framesPerSecond != 0.0f)
      m_timePerFrame = 1.0f / framesPerSecond;

    updateCurrentRectX();
  }

  void EightDirectionsSpriteSheetAnimation::play()
  {
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

    assertSpriteIsNotNull();
    updateSpeedModifier();
    updateDirectionAngle();

    if (m_timePerFrame > 0.0f)
      m_currentTime += deltaTime;
    else
      m_currentTime = -1.0f;

    while (m_currentTime >= m_timePerFrame)
    {
      m_currentTime -= m_timePerFrame;
      m_currentFrame = (m_currentFrame + 1) % m_description.getAnimationLength();
      updateCurrentRectX();
    }

    m_sprite->setTextureRect(calculateTextureRect());
  }

  void EightDirectionsSpriteSheetAnimation::updateSpeedModifier()
  {
    float speedModifier = 1.0f;
    String speedModifierKey = m_description.getSpeedModifierKey();
    if (!speedModifierKey.empty())
    {
      const BlackboardValueGroup<float>& floatValues =
        m_blackboard.getFloatValues();

      if (floatValues.hasValue(speedModifierKey))
        speedModifier = floatValues.getValue(speedModifierKey);
    }

    if (speedModifier == 0.0f)
      m_timePerFrame = 0;
    else
      m_timePerFrame = 1.0f / (m_description.getFramesPerSecond() * speedModifier);
  }

  void EightDirectionsSpriteSheetAnimation::updateDirectionAngle()
  {
    Angle angle = sf::radians(0.0f);
    String directionAngleKey = m_description.getDirectionAngleKey();
    if (!directionAngleKey.empty())
    {
      const BlackboardValueGroup<Angle>& angleValues =
        m_blackboard.getAngleValues();

      if (angleValues.hasValue(directionAngleKey))
        angle = angleValues.getValue(directionAngleKey);
    }

    updateCurrentRectY(angle);
  }

  UInt32 EightDirectionsSpriteSheetAnimation::getSpriteSheetColumnFromAngle(
    const Angle& angle
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

  void EightDirectionsSpriteSheetAnimation::updateCurrentRectX()
  {
    m_currentRectX = m_currentFrame * m_description.getFrameWidth();
  }

  void EightDirectionsSpriteSheetAnimation::updateCurrentRectY(
    const Angle& angle
  )
  {
    UInt32 spriteSheetColumn = getSpriteSheetColumnFromAngle(angle);
    m_currentRectY = spriteSheetColumn * m_description.getFrameHeight();
  }

  void EightDirectionsSpriteSheetAnimation::assertSpriteIsNotNull() const
  {
    assertions::assertNotNull(m_sprite, "animation sprite");
  }
}