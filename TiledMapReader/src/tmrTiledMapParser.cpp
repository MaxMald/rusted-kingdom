#include "TMR/tmrTiledMapParser.h"
#include "TMR/tmrTiledMap.h"
#include "TMR/tmrMapLayer.h"
#include <string>
#include <stdexcept>

namespace tmr
{
  TiledMapParser::TiledMapParser() :
    m_mapLayerParser()
  {
  }

  TiledMapParser::~TiledMapParser()
  {
  }

  TiledMap* TiledMapParser::parseFromJson(const Json& json)
  {
    bool infinite = json["infinite"].getBool();
    std::int32_t height = json["height"].getInt32();
    std::int32_t width = json["width"].getInt32();
    std::int32_t nextLayerId = json["nextlayerid"].getInt32();
    std::int32_t nextObjectId = json["nextobjectid"].getInt32();
    std::int32_t tileHeight = json["tileheight"].getInt32();
    std::int32_t tileWidth = json["tilewidth"].getInt32();

    // Parse orientation
    std::string orientationStr;
    orientationStr.resize(json["orientation"].getStringLength() + 1);
    json["orientation"].getString(&orientationStr[0], orientationStr.size());
    orientation::Type orientationVal = parseOrientation(orientationStr.c_str());

    // Parse render order
    std::string renderOrderStr;
    renderOrderStr.resize(json["renderorder"].getStringLength() + 1);
    json["renderorder"].getString(&renderOrderStr[0], renderOrderStr.size());
    renderOrder::Type renderOrderVal = parseRenderOrder(renderOrderStr.c_str());

    // Parse tiled version
    std::string tiledVersionStr;
    tiledVersionStr.resize(json["tiledversion"].getStringLength() + 1);
    json["tiledversion"].getString(&tiledVersionStr[0], tiledVersionStr.size());

    // Parse type
    std::string typeStr;
    typeStr.resize(json["type"].getStringLength() + 1);
    json["type"].getString(&typeStr[0], typeStr.size());

    // Parse version
    std::string versionStr;
    versionStr.resize(json["version"].getStringLength() + 1);
    json["version"].getString(&versionStr[0], versionStr.size());

    // Parse map layers
    Json layersJson = json["layers"];
    std::size_t layersArraySize = layersJson.getSize();
    MapLayer** layers = new MapLayer * [layersArraySize];
    for (std::size_t i = 0; i < layersArraySize; ++i)
    {
      layers[i] = m_mapLayerParser.parseFromJson(layersJson[i]);
    }

    return new TiledMap(
      infinite,
      height,
      width,
      nextLayerId,
      nextObjectId,
      tileHeight,
      tileWidth,
      orientationVal,
      renderOrderVal,
      tiledVersionStr.c_str(),
      typeStr.c_str(),
      versionStr.c_str(),
      layers,
      layersArraySize
    );
  }

  orientation::Type TiledMapParser::parseOrientation(const char* orientationStr)
  {
    if (!orientationStr)
      throw std::runtime_error("orientationStr is null");

    std::string str(orientationStr);

    if (str == "isometric")
      return orientation::Type::Isometric;

    throw std::runtime_error("Unknown orientation string: " + str);
  }

  renderOrder::Type TiledMapParser::parseRenderOrder(const char* renderOrderStr)
  {
    if (!renderOrderStr)
      throw std::runtime_error("renderOrderStr is null");

    std::string str(renderOrderStr);

    if (str == "right-down")
      return renderOrder::Type::RightDown;
    else if (str == "right-up")
      return renderOrder::Type::RightUp;
    else if (str == "left-down")
      return renderOrder::Type::LeftDown;
    else if (str == "left-up")
      return renderOrder::Type::LeftUp;

    throw std::runtime_error("Unknown render order string: " + str);
  }
}