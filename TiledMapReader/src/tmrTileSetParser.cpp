#include "TMR/tmrTileSetParser.h"

#include <string>
#include <stdexcept>

#include "TMR/tmrTileSet.h"
#include "TMR/tmrSpriteSheetTileSet.h"
#include "TMR/tmrReferenceTileSet.h"
#include "TMR/tmrImageCollectionTileSet.h"

namespace tmr
{
  TileSetParser::TileSetParser() :
    m_referenceTileSetParser()
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
      throw std::runtime_error("Unsupported tileset type in JSON.");
    }
    else if (json.contains("tiles"))
    {
      throw std::runtime_error("Unsupported tileset type in JSON.");
    }
    else if (json.contains("source"))
    {
      return m_referenceTileSetParser.parseFromJson(firstgid, json);
    }
    else
    {
      throw std::runtime_error("Unsupported tileset type in JSON.");
    }
  }
}