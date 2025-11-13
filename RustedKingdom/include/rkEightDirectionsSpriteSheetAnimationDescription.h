#pragma once

#include "rkPrerequisites.h"

namespace tmr
{
  class Json;
}

namespace rk
{
  class EightDirectionsSpriteSheetAnimationDescription
  {
  public:

    EightDirectionsSpriteSheetAnimationDescription() :
      m_animationKey(""),
      m_textureKey(""),
      m_frameWidth(0),
      m_frameHeight(0),
      m_animationLength(0),
      m_framesPerSecond(0),
      m_directionAngleKey(""),
      m_speedModifierKey(""),
      m_initialFrame(0)
    { }

    EightDirectionsSpriteSheetAnimationDescription(
      const String& animationKey,
      const String& textureKey,
      UInt32 frameWidth,
      UInt32 frameHeight,
      UInt32 animationLength,
      UInt32 initialFrame,
      float framesPerSecond,
      const String& directionAngleKey,
      const String& speedModifierKey
    ) :
      m_animationKey(animationKey),
      m_textureKey(textureKey),
      m_frameWidth(frameWidth),
      m_frameHeight(frameHeight),
      m_animationLength(animationLength),
      m_framesPerSecond(framesPerSecond),
      m_directionAngleKey(directionAngleKey),
      m_speedModifierKey(speedModifierKey),
      m_initialFrame(initialFrame)
    {
    }

    EightDirectionsSpriteSheetAnimationDescription(
      const EightDirectionsSpriteSheetAnimationDescription& other
    ) : 
      m_animationKey(other.m_animationKey),
      m_textureKey(other.m_textureKey),
      m_frameWidth(other.m_frameWidth),
      m_frameHeight(other.m_frameHeight),
      m_animationLength(other.m_animationLength),
      m_framesPerSecond(other.m_framesPerSecond),
      m_directionAngleKey(other.m_directionAngleKey),
      m_speedModifierKey(other.m_speedModifierKey),
      m_initialFrame(other.m_initialFrame)
    {
    }

    EightDirectionsSpriteSheetAnimationDescription(
      EightDirectionsSpriteSheetAnimationDescription&& other
    ) noexcept
    {
      m_animationKey = std::move(other.m_animationKey);
      m_textureKey =  std::move(other.m_textureKey);
      m_frameWidth = other.m_frameWidth;
      m_frameHeight = other.m_frameHeight;
      m_animationLength = other.m_animationLength;
      m_framesPerSecond = other.m_framesPerSecond;
      m_directionAngleKey = std::move(other.m_directionAngleKey);
      m_speedModifierKey = std::move(other.m_speedModifierKey);
      m_initialFrame = other.m_initialFrame;
    }

    ~EightDirectionsSpriteSheetAnimationDescription() = default;

    EightDirectionsSpriteSheetAnimationDescription& operator=(
      const EightDirectionsSpriteSheetAnimationDescription& other
      )
    {
      if (this != &other)
      {
        m_animationKey = other.m_animationKey;
        m_textureKey = other.m_textureKey;
        m_frameWidth = other.m_frameWidth;
        m_frameHeight = other.m_frameHeight;
        m_animationLength = other.m_animationLength;
        m_framesPerSecond = other.m_framesPerSecond;
        m_directionAngleKey = other.m_directionAngleKey;
        m_speedModifierKey = other.m_speedModifierKey;
        m_initialFrame = other.m_initialFrame;
      }
      return *this;
    }

    EightDirectionsSpriteSheetAnimationDescription& operator=(
      EightDirectionsSpriteSheetAnimationDescription&& other
      ) noexcept
    {
      if (this != &other)
      {
        m_animationKey = std::move(other.m_animationKey);
        m_textureKey = std::move(other.m_textureKey);
        m_frameWidth = other.m_frameWidth;
        m_frameHeight = other.m_frameHeight;
        m_animationLength = other.m_animationLength;
        m_framesPerSecond = other.m_framesPerSecond;
        m_directionAngleKey = std::move(other.m_directionAngleKey);
        m_speedModifierKey = std::move(other.m_speedModifierKey);
        m_initialFrame = other.m_initialFrame;
      }
      return *this;
    }

    const String& getAnimationKey() const { return m_animationKey; }
    const String& getTextureKey() const { return m_textureKey; }
    const String& getDirectionAngleKey() const { return m_directionAngleKey; }
    const String& getSpeedModifierKey() const { return m_speedModifierKey; }
    UInt32 getFrameWidth() const { return m_frameWidth; }
    UInt32 getFrameHeight() const { return m_frameHeight; }
    UInt32 getAnimationLength() const { return m_animationLength; }
    UInt32 getInitialFrame() const { return m_initialFrame; }
    float getFramesPerSecond() const { return m_framesPerSecond; }

    bool loadFromJson(const tmr::Json& json);

  private:
    String m_animationKey;
    String m_textureKey;
    String m_directionAngleKey;
    String m_speedModifierKey;
    UInt32 m_frameWidth;
    UInt32 m_frameHeight;
    UInt32 m_animationLength;
    UInt32 m_initialFrame;
    float m_framesPerSecond;
  };
}