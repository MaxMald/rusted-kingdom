#include "TMR/tmrTiledMapXmlLoader.h"

#include "TMR/tinyxml2.h"
#include "TMR/tmrTiledMap.h"
#include "TMR/tmrTileMapLayer.h"
#include "TMR/tmrTileSet.h"
#include "TMR/tmrOrientationParser.h"
#include "TMR/tmrOrientation.h"
#include "TMR/tmrRenderOrder.h"
#include "TMR/tmrRenderOrderParser.h"
#include "TMR/tmrTileSetXmlLoader.h"
#include "TMR/tmrTileMapLayerXmlLoader.h"
#include "TMR/tmrObjectGroupXmlLoader.h"
#include "TMR/tmrPathUtilities.h"

using namespace tinyxml2;

namespace tmr
{
  namespace tiledMapXmlLoader
  {
    TiledMap* loadFromFile(const char* filename)
    {
      XMLDocument doc;
      if (doc.LoadFile(filename) != XML_SUCCESS)
        return nullptr;

      char* source = pathUtilities::getDirectoryFromPath(filename);
      TiledMap* tiledMap = parseFromXmlElement(
        doc.FirstChildElement("map"),
        source
      );
      delete[] source;

      return tiledMap;
    }

    TiledMap* parseFromXmlElement(XMLElement* mapElement, const char* source)
    {
      if (!mapElement)
        return nullptr;

      bool infinite = mapElement->BoolAttribute("infinite", false);
      int32_t height = mapElement->IntAttribute("height", 0);
      int32_t width = mapElement->IntAttribute("width", 0);
      int32_t nextLayerId = mapElement->IntAttribute("nextlayerid", 0);
      int32_t nextObjectId = mapElement->IntAttribute("nextobjectid", 0);
      int32_t tileHeight = mapElement->IntAttribute("tileheight", 0);
      int32_t tileWidth = mapElement->IntAttribute("tilewidth", 0);
      const char* tiledVersion = mapElement->Attribute("tiledversion");
      const char* version = mapElement->Attribute("version");
      orientation::Type orientation = orientationParser::parseFromXmlElement(mapElement);
      renderOrder::Type renderOrder = renderOrderParser::parseFromXmlElement(mapElement);

      size_t layerCount = 0;
      TileMapLayer** layers = tileMapLayerXmlLoader::parseLayerArrayFromXmlElement(
        mapElement,
        layerCount
      );

      size_t objectGroupCount = 0;
      ObjectGroup** objectGroups = objectGroupXmlLoader::parseObjectGroupArrayFromXmlElement(
        mapElement,
        objectGroupCount
      );

      size_t tileSetCount = 0;
      TileSet** tileSets = tileSetXmlLoader::parseTileSetArray(
        mapElement,
        tileSetCount,
        source
      );

      return new TiledMap(
        infinite,
        height,
        width,
        nextLayerId,
        nextObjectId,
        tileHeight,
        tileWidth,
        orientation,
        renderOrder,
        tiledVersion ? tiledVersion : "",
        "map",
        version ? version : "",
        layers,
        layerCount,
        objectGroups,
        objectGroupCount,
        tileSets,
        tileSetCount
      );
    }
  }
}