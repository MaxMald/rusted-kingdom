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
    m_spriteSheetTileSetParser(),
    m_referenceTileSetParser(),
    m_imageCollectionTileSetParser()
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
      return m_imageCollectionTileSetParser.parseFromJson(firstgid, json);
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