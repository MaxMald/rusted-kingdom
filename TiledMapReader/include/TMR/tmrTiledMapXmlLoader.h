#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  class TiledMap;
  class TileSet;
  class GridDataLayer;
  class ObjectGroup;

  namespace tiledMapXmlLoader
  {
    TiledMap* loadFromFile(const char* filename);
    TiledMap* parseFromXmlElement(XMLElement* mapElement, const char* source);
  }
}