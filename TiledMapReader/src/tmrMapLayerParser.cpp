#include "TMR/tmrMapLayerParser.h"
#include "TMR/tmrTileMapLayer.h"
#include "TMR/tmrObjectGroupMapLayer.h"
#include <string>
#include <stdexcept>

namespace tmr
{
  MapLayerParser::MapLayerParser() :
    m_tileMapLayerParser(),
    m_objectGroupMapLayerParser()
  {
  }

  MapLayerParser::~MapLayerParser()
  {
  }

  MapLayer* MapLayerParser::parseFromJson(const Json& json)
  {
    std::int32_t id = json["id"].getInt32();
    std::int32_t x = json["x"].getInt32();
    std::int32_t y = json["y"].getInt32();
    bool visible = json["visible"].getBool();
    float opacity = json["opacity"].getFloat();

    // Parse name
    std::string nameStr;
    nameStr.resize(json["name"].getStringLength() + 1);
    json["name"].getString(&nameStr[0], nameStr.size());

    // Parse type
    std::string typeStr;
    typeStr.resize(json["type"].getStringLength() + 1);
    json["type"].getString(&typeStr[0], typeStr.size());

    if (typeStr == "tilelayer")
    {
      return m_tileMapLayerParser.parseFromJson(
        id,
        x, y,
        visible,
        opacity,
        nameStr.c_str(),
        json
      );
    }
    else if(typeStr == "objectgroup")
    {
      return m_objectGroupMapLayerParser.parseFromJson(
        id,
        x, y,
        visible,
        opacity,
        nameStr.c_str(),
        json
      );
    }
    else
    {
      throw std::runtime_error("Unsupported layer type: " + typeStr);
    }
  }
}