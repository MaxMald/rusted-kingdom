#include "TMR/tmrTileSetGridParser.h"
#include "TMR/tmrTileSetGrid.h"
#include "TMR/tmrOrientationParser.h"
#include <string>

namespace tmr
{
  TileSetGridParser::TileSetGridParser()
  {
  }

  TileSetGridParser::~TileSetGridParser()
  {
  }

  TileSetGrid* TileSetGridParser::parseFromJson(const Json& json)
  {
    std::uint32_t width = static_cast<std::uint32_t>(json["width"].getInt32());
    std::uint32_t height = static_cast<std::uint32_t>(json["height"].getInt32());

    // Parse orientation
    std::string nameStr;
    nameStr.resize(json["name"].getStringLength() + 1);
    json["name"].getString(&nameStr[0], nameStr.size());
    nameStr.resize(nameStr.size() - 1);
    orientation::Type orientation = orientationParser::parseFromString(nameStr.c_str());

    return new TileSetGrid(
      width,
      height,
      orientation
    );
  }
}