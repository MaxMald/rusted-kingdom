#include "TMR/tmrTileSetParser.h"

#include <string>
#include <stdexcept>

#include "TMR/tmrTileSet.h"
#include "TMR/tmrSpriteSheetTileSet.h"

namespace tmr
{
  TileSetParser::TileSetParser() :
    m_spriteSheetTileSetParser()
  {
  }

  TileSetParser::~TileSetParser()
  {
  }

  TileSet* TileSetParser::parseFromJson(const Json& json)
  {
    std::int32_t firstgid = json["firstgid"].getInt32();

    if (json.contains("image"))
    {
      return m_spriteSheetTileSetParser.parseFromJson(firstgid, json);
    }
    else if (json.contains("tiles"))
    {
      throw std::runtime_error("TODO: Implement collection tileset parsing");
    }
    else if (json.contains("source"))
    {
      throw std::runtime_error("TODO: Implement source tileset parsing");
    }
    else
    {
      throw std::runtime_error("Unsupported tileset type in JSON.");
    }
  }
}