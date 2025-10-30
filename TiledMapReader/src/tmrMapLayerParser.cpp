#include "TMR/tmrMapLayerParser.h"
#include "TMR/tmrTileMapLayer.h"
#include "TMR/tmrObjectGroupMapLayer.h"
#include <string>
#include <stdexcept>

namespace tmr
{
  static inline std::string jsonToStdString(const Json& j)
  {
    const std::size_t len = j.getStringLength();
    std::string s;

    // reserve for terminator written by getString
    s.resize(len + 1);
    j.getString(&s[0], s.size());

    // drop the explicit terminator
    s.resize(len);
    return s;
  }

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
    std::string typeStr = jsonToStdString(json["type"]);

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