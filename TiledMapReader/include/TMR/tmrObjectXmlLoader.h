#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  class Object;

  namespace objectXmlLoader
  {
    Object* parseObjectFromXmlElement(XMLElement* objectElement);
    Object** parseObjectArrayFromXmlElement(
      XMLElement* parentElement,
      size_t& outObjectCount
    );
  }
}