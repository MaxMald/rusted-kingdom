#include "rkEightDirAnimationDesc.h"

#include <vector>
#include <cstring>
#include <TMR/tmrJson.h>

#include "rkJsonUtilities.h"

using tmr::Json;

namespace rk
{
  EightDirAnimationDesc::EightDirAnimationDesc() :
    m_animationKey(""),
    m_textureKey(""),
    m_frameWidth(0),
    m_frameHeight(0),
    m_animationLength(0),
    m_framesPerSecond(0),
    m_directionAngleKey(""),
    m_speedModifierKey(""),
    m_initialFrame(0)
  {
  }

  bool EightDirAnimationDesc::loadFromFile(const Path& filename)
  {
    try
    {
      Json json = Json::loadFromFile(filename.string().c_str());

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