#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  class GridDataLayer;
  class Data;

  namespace gridDataLayerXmlLoader
  {
    GridDataLayer* parseLayerFromXmlElement(XMLElement* layerElement);
    GridDataLayer** parseLayerArrayFromXmlElement(
      XMLElement* layersParentElement,
      size_t& outLayerCount
    );
    Data* parseDataFromXmlElement(XMLElement* dataElement);
  }
}