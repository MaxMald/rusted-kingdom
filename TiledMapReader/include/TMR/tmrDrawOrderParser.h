#pragma once

#include "TMR/tmrDrawOrder.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  namespace drawOrderParser
  {
    drawOrder::Type parseFromXmlElement(XMLElement* element);
    drawOrder::Type parseFromString(const char* str);
  }
}