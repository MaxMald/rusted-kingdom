#include "TMR/tmrTileSetTileParser.h"
#include "TMR/tmrTileSetTile.h"
#include <string>

namespace tmr
{
  TileSetTileParser::TileSetTileParser()
  {
  }

  TileSetTileParser::~TileSetTileParser()
  {
  }

  TileSetTile* TileSetTileParser::parseFromJson(const Json& json)
  {
    std::uint32_t id = static_cast<std::uint32_t>(json["id"].getInt32());
    std::uint32_t imageWidth = static_cast<std::uint32_t>(json["imagewidth"].getInt32());
    std::uint32_t imageHeight = static_cast<std::uint32_t>(json["imageheight"].getInt32());

    // Parse image string
    std::string imageStr;
    imageStr.resize(json["image"].getStringLength() + 1);
    json["image"].getString(&imageStr[0], imageStr.size());
    imageStr.resize(imageStr.size() - 1);

    return new TileSetTile(
      id,
      imageWidth,
      imageHeight,
      imageStr.c_str()
    );
  }
}