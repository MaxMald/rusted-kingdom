#pragma once

#include "rkIAsset.h"

namespace rk
{
  /**
   * @brief Describes an eight-directional sprite sheet animation asset.
   */
  class EightDirAnimationDesc : public IAsset
  {
  public:

    EightDirAnimationDesc();
    virtual ~EightDirAnimationDesc() = default;

    const String& getAnimationKey() const { return m_animationKey; }
    const String& getTextureKey() const { return m_textureKey; }
    const String& getDirectionAngleKey() const { return m_directionAngleKey; }
    const String& getSpeedModifierKey() const { return m_speedModifierKey; }
    UInt32 getFrameWidth() const { return m_frameWidth; }
    UInt32 getFrameHeight() const { return m_frameHeight; }
    UInt32 getAnimationLength() const { return m_animationLength; }
    UInt32 getInitialFrame() const { return m_initialFrame; }
    float getFramesPerSecond() const { return m_framesPerSecond; }

  protected:
    virtual bool loadFromFile(const Path& filename) override;
    virtual void unload() override {}

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