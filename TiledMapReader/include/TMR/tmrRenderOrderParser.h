#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrRenderOrder.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  namespace renderOrderParser
  {
    renderOrder::Type parseFromXmlElement(XMLElement* element);
    renderOrder::Type parseFromString(const char* str);
  }
}