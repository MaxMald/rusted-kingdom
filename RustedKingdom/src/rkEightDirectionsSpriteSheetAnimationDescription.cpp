#include "rkEightDirectionsSpriteSheetAnimationDescription.h"

#include <TMR/tmrJson.h>
#include <vector>
#include <cstring>

#include "rkJsonUtilities.h"

namespace rk
{
  bool EightDirectionsSpriteSheetAnimationDescription::loadFromJson(
    const tmr::Json& json
  )
  {
    try
    {
      m_animationKey = jsonUtilities::getStringFromJson(json["animationKey"]);
      m_textureKey = jsonUtilities::getStringFromJson(json["textureKey"]);
      m_frameWidth = static_cast<UInt32>(json["frameWidth"].getInt32());
      m_frameHeight = static_cast<UInt32>(json["frameHeight"].getInt32());
      m_animationLength = static_cast<UInt32>(json["animationLength"].getInt32());
      m_initialFrame = static_cast<UInt32>(json["initialFrame"].getInt32());
      m_framesPerSecond = json["framesPerSecond"].getFloat();
      m_directionAngleKey = jsonUtilities::getStringFromJson(json["directionAngleKey"]);
      m_speedModifierKey = jsonUtilities::getStringFromJson(json["speedModifierKey"]);

      return true;
    }
    catch (const std::exception&)
    {
      return false;
    }
  }
}