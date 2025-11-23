#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tinyxml2.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  class TileSet;
  class TileSetTile;
  class TileSetGrid;
  class Image;

  namespace tileSetXmlLoader
  {
    TileSet* loadFromFile(const char* filePath, const int32_t firstGid);
    TileSet* parseFromXmlElement(XMLElement* tilesetElement, const int32_t firstGid, const char* sourcePath);
    TileSet* parseFromXmlElement(XMLElement* tilesetElement, const char* sourcePath);
    TileSet* parseSpriteSheetTileSet(XMLElement* tilesetElement, const int32_t firstGid, const char* source);
    TileSet* parseImageCollectionTileSet(XMLElement* tilesetElement, const int32_t firstGid, const char* source);
    TileSet** parseTileSetArray(XMLElement* tileSetParent, size_t& outTileCount, const char* source);
    TileSetGrid* parseTileSetGrid(XMLElement* gridElement);
    TileSetTile** parseTileSetTileArray(XMLElement* tilesetElement, size_t tileCount, const char* source);
    TileSetTile* parseTileSetTile(XMLElement* tileElement, const char* source);
    Image* parseImage(XMLElement* imageElement, const char* source);
  };
}