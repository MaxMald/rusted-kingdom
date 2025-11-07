#include "TMR/tmrObjectGroupMapLayerParser.h"

#include <string>
#include <stdexcept>

#include "TMR/tmrObjectGroupMapLayer.h"
#include "TMR/tmrDrawOrderParser.h"

namespace tmr
{
  ObjectGroupMapLayerParser::ObjectGroupMapLayerParser() :
    m_objectParser()
  {
  }

  ObjectGroupMapLayerParser::~ObjectGroupMapLayerParser()
  {
  }

  ObjectGroupMapLayer* ObjectGroupMapLayerParser::parseFromJson(
    const std::int32_t id,
    const std::int32_t x,
    const std::int32_t y,
    const bool& visible,
    const float& opacity,
    const char* name,
    const Json& json
  )
  {
    // Parse draw order
    std::string drawOrderStr;
    drawOrderStr.resize(json["draworder"].getStringLength() + 1);
    json["draworder"].getString(&drawOrderStr[0], drawOrderStr.size());
    drawOrder::Type drawOrder = drawOrderParser::parseFromString(drawOrderStr.c_str());

    // Parse objects
    Json objectsJson = json["objects"];
    if (!objectsJson.isArray())
      throw std::runtime_error("Invalid JSON: 'objects' is not an array");

    std::size_t objectsSize = objectsJson.getSize();
    Object** objects = new Object* [objectsSize];

    for (std::size_t i = 0; i < objectsSize; ++i)
      objects[i] = m_objectParser.parseFromJson(objectsJson[i]);

    return new ObjectGroupMapLayer(
      id,
      x, y,
      visible,
      opacity,
      name,
      drawOrder,
      objects,
      objectsSize
    );
  }
}