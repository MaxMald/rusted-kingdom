#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"
#include "TMR/tmrTileSetGridParser.h"
#include "TMR/tmrTileSetTileParser.h"

namespace tmr
{
  class ImageCollectionTileSet;

  class ImageCollectionTileSetParser
  {
  public:

    ImageCollectionTileSetParser();
    ~ImageCollectionTileSetParser();

    ImageCollectionTileSet* parseFromJson(
      const std::int32_t firstgid,
      const Json& json
    );

  private:
    TileSetGridParser m_tileSetGridParser;
    TileSetTileParser m_tileSetTileParser;

    TileSetTile** parseTileSetArray(
      const std::uint32_t numTiles,
      const Json& json
    );
  };
}