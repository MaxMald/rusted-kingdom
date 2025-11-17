#include "TMR/tmrObjectGroupParser.h"

#include <string>
#include <stdexcept>

#include "TMR/tmrObjectGroup.h"
#include "TMR/tmrDrawOrderParser.h"

namespace tmr
{
  ObjectGroupParser::ObjectGroupParser()
  {
  }

  ObjectGroupParser::~ObjectGroupParser()
  {
  }

  ObjectGroup* ObjectGroupParser::parseFromJson(const Json& json)
  {
    std::int32_t id = static_cast<std::int32_t>(json["id"].getInt32());
    std::int32_t x = static_cast<std::int32_t>(json["x"].getInt32());
    std::int32_t y = static_cast<std::int32_t>(json["y"].getInt32());
    bool visible = json["visible"].getBool();
    float opacity = json["opacity"].getFloat();

    // Parse name
    std::string nameStr;
    nameStr.resize(json["name"].getStringLength() + 1);
    json["name"].getString(&nameStr[0], nameStr.size());
    nameStr.resize(nameStr.size() - 1);

    std::string drawOrderStr;
    drawOrderStr.resize(json["draworder"].getStringLength() + 1);
    json["draworder"].getString(&drawOrderStr[0], drawOrderStr.size());
    drawOrder::Type drawOrder = drawOrderParser::parseFromString(drawOrderStr.c_str());

    // Parse objects
    Json objectsJson = json["objects"];
    if (!objectsJson.isArray())
      throw std::runtime_error("Invalid JSON: 'objects' is not an array");

    std::size_t objectsSize = objectsJson.getSize();
    Object** objects = new Object * [objectsSize];

    for (std::size_t i = 0; i < objectsSize; ++i)
      objects[i] = m_objectParser.parseFromJson(objectsJson[i]);

    return new ObjectGroup(
      id,
      x, y,
      visible,
      opacity,
      nameStr.c_str(),
      drawOrder,
      objects,
      objectsSize
    );
  }
}