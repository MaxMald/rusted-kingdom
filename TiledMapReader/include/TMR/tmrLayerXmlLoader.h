#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  class Layer;

  namespace layerXmlLoader
  {
    Layer* parseLayerFromXmlElement(XMLElement* layerElement);
    bool isLayerXmlElement(XMLElement* element);
  }
}