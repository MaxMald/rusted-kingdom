#include "TMR/tmrTileSetXmlLoader.h"

#include <string>

using std::string;

#include "TMR/tinyxml2.h"
#include "TMR/tmrOrientation.h"
#include "TMR/tmrOrientationParser.h"
#include "TMR/tmrTileSetGrid.h"
#include "TMR/tmrTileSetTile.h"
#include "TMR/tmrImageCollectionTileSet.h"
#include "TMR/tmrSpriteSheetTileSet.h"
#include "TMR/tmrImage.h"

using namespace tinyxml2;

namespace tmr
{
  namespace tileSetXmlLoader
  {
    TileSet* loadFromFile(const char* filePath, const int32_t firstGid)
    {
      XMLDocument doc;
      XMLError loadResult = doc.LoadFile(filePath);
      if (loadResult != XML_SUCCESS)
        return nullptr;

      XMLElement* tilesetElement = doc.FirstChildElement("tileset");
      if (!tilesetElement)
        return nullptr;

      XMLElement* gridElement = tilesetElement->FirstChildElement("grid");
      if (gridElement)
        return parseImageCollectionTileSet(tilesetElement, firstGid);

      XMLElement* imageElement = tilesetElement->FirstChildElement("image");
      if (imageElement)
        return parseSpriteSheetTileSet(tilesetElement, firstGid);

      return nullptr;
    }

    TileSet* parseSpriteSheetTileSet(
      XMLElement* tilesetElement,
      const int32_t firstGid
    )
    {
      int32_t margin = tilesetElement->IntAttribute("margin", 0);
      uint32_t spacing = tilesetElement->UnsignedAttribute("spacing", 0);
      uint32_t columns = tilesetElement->UnsignedAttribute("columns", 0);
      uint32_t tileCount = tilesetElement->UnsignedAttribute("tilecount", 0);
      uint32_t tileHeight = tilesetElement->UnsignedAttribute("tileheight", 0);
      uint32_t tileWidth = tilesetElement->UnsignedAttribute("tilewidth", 0);
      const char* nameCStr = tilesetElement->Attribute("name");
      Image* image = parseImage(tilesetElement->FirstChildElement("image"));

      return new SpriteSheetTileSet(
        image,
        margin,
        firstGid,
        columns,
        spacing,
        tileCount,
        tileHeight,
        tileWidth,
        nameCStr ? nameCStr : ""
      );
    }

    TileSet* parseImageCollectionTileSet(
      XMLElement* tilesetElement,
      const int32_t firstGid
    )
    {
      int32_t margin = tilesetElement->IntAttribute("margin", 0);
      uint32_t spacing = tilesetElement->UnsignedAttribute("spacing", 0);
      uint32_t columns = tilesetElement->UnsignedAttribute("columns", 0);
      size_t tileCount = static_cast<size_t>(tilesetElement->IntAttribute("tilecount", 0));
      uint32_t tileHeight = tilesetElement->UnsignedAttribute("tileheight", 0);
      uint32_t tileWidth = tilesetElement->UnsignedAttribute("tilewidth", 0);
      const char* nameCStr = tilesetElement->Attribute("name");
      TileSetGrid* tileSetGrid = parseTileSetGrid(tilesetElement->FirstChildElement("grid"));
      TileSetTile** tiles = parseTileSetTileArray(tilesetElement, tileCount);

      return new ImageCollectionTileSet(
        firstGid,
        tileSetGrid,
        tiles,
        tileCount,
        columns,
        margin,
        spacing,
        tileHeight,
        tileWidth,
        nameCStr ? nameCStr : ""
      );
    }

    TileSetGrid* parseTileSetGrid(XMLElement* gridElement)
    {
      if (!gridElement)
        return nullptr;

      int32_t width = gridElement->IntAttribute("width", 0);
      int32_t height = gridElement->IntAttribute("height", 0);

      const char* orientationStr = gridElement->Attribute("orientation");
      orientation::Type orientation = orientation::Type::Orthogonal;
      if (orientationStr)
        orientation = orientationParser::parseFromString(orientationStr);

      return new TileSetGrid(width, height, orientation);
    }

    TileSetTile** parseTileSetTileArray(
      XMLElement* tilesetElement,
      size_t tileCount
    )
    {
      TileSetTile** tiles = new TileSetTile * [tileCount];

      size_t i = 0;
      XMLElement* tileElement = tilesetElement->FirstChildElement("tile");
      while (tileElement)
      {
        if (i >= tileCount)
          break;

        tiles[i] = parseTileSetTile(tileElement);

        tileElement = tileElement->NextSiblingElement("tile");
        ++i;
      }

      return tiles;
    }

    TileSetTile* parseTileSetTile(XMLElement* tileElement)
    {
      if (!tileElement)
        return nullptr;

      uint32_t id = tileElement->UnsignedAttribute("id", 0);
      Image* image = parseImage(tileElement->FirstChildElement("image"));
      return new TileSetTile(id, image);
    }

    Image* parseImage(XMLElement* imageElement)
    {
      if (!imageElement)
        return nullptr;

      const char* source = imageElement->Attribute("source");
      uint32_t width = imageElement->UnsignedAttribute("width", 0);
      uint32_t height = imageElement->UnsignedAttribute("height", 0);

      return new Image(
        source ? source : "",
        width,
        height
      );
    }
  };
}
