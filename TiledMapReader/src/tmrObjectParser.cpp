#include "TMR/tmrObjectParser.h"

#include <string>

#include "TMR/tmrObject.h"

namespace tmr
{
  ObjectParser::ObjectParser()
  {
  }
  
  ObjectParser::~ObjectParser()
  {
  }

  Object* ObjectParser::parseFromJson(const Json& json)
  {
    std::uint32_t gid = static_cast<std::uint32_t>(json["gid"].getInt32());
    std::uint32_t id = static_cast<std::uint32_t>(json["id"].getInt32());
    std::uint32_t height = static_cast<std::uint32_t>(json["height"].getInt32());
    std::uint32_t width = static_cast<std::uint32_t>(json["width"].getInt32());
    bool visible = json["visible"].getBool();
    float rotation = json["rotation"].getFloat();
    float x = json["x"].getFloat();
    float y = json["y"].getFloat();

    // Parse name
    std::string nameStr;
    nameStr.resize(json["name"].getStringLength() + 1);
    json["name"].getString(&nameStr[0], nameStr.size());
    // drop explicit terminator written by getString
    nameStr.resize(nameStr.size() - 1);

    // Parse type
    std::string typeStr;
    typeStr.resize(json["type"].getStringLength() + 1);
    json["type"].getString(&typeStr[0], typeStr.size());
    typeStr.resize(typeStr.size() - 1);

    return new Object(
      gid,
      id,
      height,
      width,
      visible,
      rotation,
      x,
      y,
      nameStr.c_str(),
      typeStr.c_str()
    );
  }
}