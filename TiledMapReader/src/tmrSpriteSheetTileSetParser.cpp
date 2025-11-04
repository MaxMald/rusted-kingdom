#include "TMR/tmrSpriteSheetTileSetParser.h"

#include <string>

#include "TMR/tmrSpriteSheetTileSet.h"

namespace tmr
{
  SpriteSheetTileSetParser::SpriteSheetTileSetParser()
  {
  }

  SpriteSheetTileSetParser::~SpriteSheetTileSetParser()
  {
  }

  SpriteSheetTileSet* SpriteSheetTileSetParser::parseFromJson(
    const std::int32_t firstgid,
    const Json& json
  )
  {
    std::int32_t margin = json["margin"].getInt32();
    std::uint32_t columns = static_cast<std::uint32_t>(json["columns"].getInt32());
    std::uint32_t imageHeight = static_cast<std::uint32_t>(json["imageheight"].getInt32());
    std::uint32_t imageWidth = static_cast<std::uint32_t>(json["imagewidth"].getInt32());
    std::uint32_t spacing = static_cast<std::uint32_t>(json["spacing"].getInt32());
    std::uint32_t tileCount = static_cast<std::uint32_t>(json["tilecount"].getInt32());
    std::uint32_t tileHeight = static_cast<std::uint32_t>(json["tileheight"].getInt32());
    std::uint32_t tileWidth = static_cast<std::uint32_t>(json["tilewidth"].getInt32());

    // Parse image string
    std::string imageStr;
    imageStr.resize(json["image"].getStringLength() + 1);
    json["image"].getString(&imageStr[0], imageStr.size());
    // drop explicit terminator written by getString
    imageStr.resize(imageStr.size() - 1);

    // Parse name string
    std::string nameStr;
    nameStr.resize(json["name"].getStringLength() + 1);
    json["name"].getString(&nameStr[0], nameStr.size());
    nameStr.resize(nameStr.size() - 1);

    return new SpriteSheetTileSet(
      margin,
      firstgid,
      columns,
      imageHeight,
      imageWidth,
      spacing,
      tileCount,
      tileHeight,
      tileWidth,
      imageStr.c_str(),
      nameStr.c_str()
    );
  }
}