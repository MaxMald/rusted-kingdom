#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tinyxml2.h"

using namespace tinyxml2;

using std::uint32_t;
using std::int32_t;
using std::size_t;

namespace tmr
{
  class TileSet;
  class TileSetTile;
  class TileSetGrid;
  class Image;

  namespace tileSetXmlLoader
  {
    TileSet* loadFromFile(const char* filePath, const int32_t firstGid);
    TileSet* parseSpriteSheetTileSet(XMLElement* tilesetElement, const int32_t firstGid);
    TileSet* parseImageCollectionTileSet(XMLElement* tilesetElement, const int32_t firstGid);
    TileSetGrid* parseTileSetGrid(XMLElement* gridElement);
    TileSetTile** parseTileSetTileArray(XMLElement* tilesetElement, size_t tileCount);
    TileSetTile* parseTileSetTile(XMLElement* tileElement);
    Image* parseImage(XMLElement* imageElement);
  };
}