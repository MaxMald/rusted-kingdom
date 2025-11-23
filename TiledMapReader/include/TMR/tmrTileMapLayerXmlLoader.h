#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  class TileMapLayer;
  class Data;

  namespace tileMapLayerXmlLoader
  {
    TileMapLayer* parseLayerFromXmlElement(XMLElement* layerElement);
    TileMapLayer** parseLayerArrayFromXmlElement(
      XMLElement* layersParentElement,
      size_t& outLayerCount
    );
    Data* parseDataFromXmlElement(XMLElement* dataElement);
  }
}