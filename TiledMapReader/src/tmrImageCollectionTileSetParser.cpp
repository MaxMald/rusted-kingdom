#include "TMR/tmrImageCollectionTileSetParser.h"

#include <string>
#include <stdexcept>

#include "TMR/tmrImageCollectionTileSet.h"

namespace tmr
{
  ImageCollectionTileSetParser::ImageCollectionTileSetParser() :
    m_tileSetGridParser()
  {
  }

  ImageCollectionTileSetParser::~ImageCollectionTileSetParser()
  {
  }

  ImageCollectionTileSet* ImageCollectionTileSetParser::parseFromJson(
    const std::int32_t firstgid,
    const Json& json
  )
  {
    // Basic numeric fields
    std::int32_t margin = json["margin"].getInt32();
    std::uint32_t columns = static_cast<std::uint32_t>(json["columns"].getInt32());
    std::uint32_t spacing = static_cast<std::uint32_t>(json["spacing"].getInt32());
    std::size_t tileCount = static_cast<std::size_t>(json["tilecount"].getInt32());
    std::uint32_t tileHeight = static_cast<std::uint32_t>(json["tileheight"].getInt32());
    std::uint32_t tileWidth = static_cast<std::uint32_t>(json["tilewidth"].getInt32());

    // Parse optional name string
    std::string nameStr;
    if (json.contains("name"))
    {
      nameStr.resize(json["name"].getStringLength() + 1);
      json["name"].getString(&nameStr[0], nameStr.size());
      nameStr.resize(nameStr.size() - 1);
    }

    TileSetGrid* tileSetGrid = m_tileSetGridParser.parseFromJson(json["grid"]);
    TileSetTile** tiles = parseTileSetArray(
      static_cast<std::uint32_t>(tileCount), 
      json["tiles"]
    );

    ImageCollectionTileSet* imageCollectionSet = new ImageCollectionTileSet(
      firstgid,
      *tileSetGrid,
      tiles,
      tileCount,
      columns,
      margin,
      spacing,
      tileHeight,
      tileWidth,
      nameStr.c_str()
    );

    delete tileSetGrid;
    return imageCollectionSet;
  }

  TileSetTile** ImageCollectionTileSetParser::parseTileSetArray(
    const std::uint32_t numTiles,
    const Json& json
  )
  {
    if (numTiles == 0)
      return nullptr;

    if (!json.isArray())
      throw std::runtime_error(
        "ImageCollectionTileSetParser::parseTileSetArray: "
        "Expected JSON array for tiles."
      );

    TileSetTile** tiles = new TileSetTile*[numTiles];
    for(std::uint32_t i = 0; i < numTiles; ++i)
    {
      tiles[i] = m_tileSetTileParser.parseFromJson(json[i]);
    }

    return tiles;
  }
}