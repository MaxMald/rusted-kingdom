#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrOrientation.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  namespace orientationParser
  {
    orientation::Type parseFromXmlElement(XMLElement* element);
    orientation::Type parseFromString(const char* orientationStr);
  } 
}