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
#include "TMR/tmrPathUtilities.h"

using namespace tinyxml2;

namespace tmr
{
  namespace tileSetXmlLoader
  {
    TileSet* loadFromFile(const char* filePath, const int32_t firstGid)
    {
      if (filePath == nullptr)
        return nullptr;

      XMLDocument doc;
      XMLError loadResult = doc.LoadFile(filePath);
      if (loadResult != XML_SUCCESS)
        return nullptr;

      XMLElement* rootElement = doc.RootElement();

      char* directoryPath = pathUtilities::getDirectoryFromPath(filePath);
      TileSet* tileSet = parseFromXmlElement(rootElement, firstGid, directoryPath);
      delete[] directoryPath;

      return tileSet;
    }

    TileSet* parseFromXmlElement(XMLElement* tilesetElement, const int32_t firstGid, const char* sourcePath)
    {
      if (!tilesetElement || !sourcePath)
        return nullptr;

      // Embedded Image collection tile set
      XMLElement* gridElement = tilesetElement->FirstChildElement("tile");
      if (gridElement)
        return parseImageCollectionTileSet(tilesetElement, firstGid, sourcePath);

      // Embedded Sprite Sheet tile set
      XMLElement* imageElement = tilesetElement->FirstChildElement("image");
      if (imageElement)
        return parseSpriteSheetTileSet(tilesetElement, firstGid, sourcePath);

      // External tile set file
      const char* source = tilesetElement->Attribute("source");
      if (source)
      {
        char* fullPath = pathUtilities::combinePaths(sourcePath, source);
        TileSet* tileSet = loadFromFile(fullPath, firstGid);
        delete[] fullPath;

        return tileSet;
      }

      return nullptr;
    }

    TileSet* parseFromXmlElement(XMLElement* tilesetElement, const char* sourcePath)
    {
      if (!tilesetElement || !sourcePath)
        return nullptr;

      int32_t firstGid = tilesetElement->IntAttribute("firstgid", 0);
      
      return parseFromXmlElement(tilesetElement, firstGid, sourcePath);
    }

    TileSet* parseSpriteSheetTileSet(
      XMLElement* tilesetElement,
      const int32_t firstGid,
      const char* source
    )
    {
      if (!tilesetElement || !source)
        return nullptr;

      int32_t margin = tilesetElement->IntAttribute("margin", 0);
      uint32_t spacing = tilesetElement->UnsignedAttribute("spacing", 0);
      uint32_t columns = tilesetElement->UnsignedAttribute("columns", 0);
      uint32_t tileCount = tilesetElement->UnsignedAttribute("tilecount", 0);
      uint32_t tileHeight = tilesetElement->UnsignedAttribute("tileheight", 0);
      uint32_t tileWidth = tilesetElement->UnsignedAttribute("tilewidth", 0);
      const char* nameCStr = tilesetElement->Attribute("name");
      TileSetGrid* tileSetGrid = parseTileSetGrid(tilesetElement->FirstChildElement("grid"));
      Image* image = parseImage(tilesetElement->FirstChildElement("image"), source);

      return new SpriteSheetTileSet(
        tileSetGrid,
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
      const int32_t firstGid,
      const char* source
    )
    {
      if (!tilesetElement || !source)
        return nullptr;

      int32_t margin = tilesetElement->IntAttribute("margin", 0);
      uint32_t spacing = tilesetElement->UnsignedAttribute("spacing", 0);
      uint32_t columns = tilesetElement->UnsignedAttribute("columns", 0);
      size_t tileCount = static_cast<size_t>(tilesetElement->IntAttribute("tilecount", 0));
      uint32_t tileHeight = tilesetElement->UnsignedAttribute("tileheight", 0);
      uint32_t tileWidth = tilesetElement->UnsignedAttribute("tilewidth", 0);
      const char* nameCStr = tilesetElement->Attribute("name");
      TileSetGrid* tileSetGrid = parseTileSetGrid(tilesetElement->FirstChildElement("grid"));
      TileSetTile** tiles = parseTileSetTileArray(tilesetElement, tileCount, source);

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

    TileSet** parseTileSetArray(
      XMLElement* tileSetParent,
      size_t& outTileCount,
      const char* source
    )
    {
      if (!tileSetParent || !source)
      {
        outTileCount = 0;
        return nullptr;
      }

      outTileCount = static_cast<size_t>(tileSetParent->ChildElementCount("tileset"));
      if (outTileCount == 0)
        return nullptr;

      TileSet** tileSets = new TileSet * [outTileCount];
      
      size_t i = 0;
      XMLElement* tileSetElement = tileSetParent->FirstChildElement("tileset");
      while (tileSetElement)
      {
        tileSets[i] = parseFromXmlElement(tileSetElement, source);
        tileSetElement = tileSetElement->NextSiblingElement("tileset");
        ++i;
      }

      return tileSets;
    }

    TileSetGrid* parseTileSetGrid(XMLElement* gridElement)
    {
      if (!gridElement)
        return nullptr;

      int32_t width = gridElement->IntAttribute("width", 0);
      int32_t height = gridElement->IntAttribute("height", 0);
      orientation::Type orientation = orientationParser::parseFromXmlElement(gridElement);

      return new TileSetGrid(width, height, orientation);
    }

    TileSetTile** parseTileSetTileArray(
      XMLElement* tilesetElement,
      size_t tileCount,
      const char* source
    )
    {
      if (!tilesetElement || tileCount == 0 || !source)
        return nullptr;

      TileSetTile** tiles = new TileSetTile * [tileCount];

      size_t i = 0;
      XMLElement* tileElement = tilesetElement->FirstChildElement("tile");
      while (tileElement)
      {
        if (i >= tileCount)
          break;

        tiles[i] = parseTileSetTile(tileElement, source);

        tileElement = tileElement->NextSiblingElement("tile");
        ++i;
      }

      return tiles;
    }

    TileSetTile* parseTileSetTile(XMLElement* tileElement, const char* source)
    {
      if (!tileElement || !source)
        return nullptr;

      uint32_t id = tileElement->UnsignedAttribute("id", 0);
      Image* image = parseImage(tileElement->FirstChildElement("image"), source);
      return new TileSetTile(id, image);
    }

    Image* parseImage(XMLElement* imageElement, const char* source)
    {
      if (!imageElement || !source)
        return nullptr;

      const char* imageSource = imageElement->Attribute("source");
      if (!imageSource)
        return nullptr;

      char* fullFilename = pathUtilities::combinePaths(source, imageSource);

      uint32_t width = imageElement->UnsignedAttribute("width", 0);
      uint32_t height = imageElement->UnsignedAttribute("height", 0);

      Image* image = new Image(
        fullFilename,
        width,
        height
      );

      delete[] fullFilename;
      return image;
    }
  };
}
