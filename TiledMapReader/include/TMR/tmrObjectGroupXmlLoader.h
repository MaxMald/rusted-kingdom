#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  class ObjectGroup;
  class Object;

  namespace objectGroupXmlLoader
  {
    ObjectGroup* parseObjectGroupFromXmlElement(XMLElement* objectGroupElement);
    ObjectGroup** parseObjectGroupArrayFromXmlElement(
      XMLElement* parentElement,
      size_t& outObjectGroupCount
    );
    Object* parseObjectFromXmlElement(XMLElement* objectElement);
    Object** parseObjectArrayFromXmlElement(
      XMLElement* parentElement,
      size_t& outObjectCount
    );
  }
}