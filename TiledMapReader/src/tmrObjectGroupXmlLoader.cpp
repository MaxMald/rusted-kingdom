#include "TMR/tmrObjectGroupXmlLoader.h"

#include <vector>

#include "TMR/tinyxml2.h"
#include "TMR/tmrObjectGroup.h"
#include "TMR/tmrObject.h"
#include "TMR/tmrDrawOrderParser.h"
#include "TMR/tmrObjectXmlLoader.h"

using namespace tinyxml2;

namespace tmr
{
  namespace objectGroupXmlLoader
  {
    ObjectGroup* parseObjectGroupFromXmlElement(XMLElement* objectGroupElement)
    {
      if (objectGroupElement == nullptr)
        return nullptr;

      int32_t id = objectGroupElement->IntAttribute("id", 0);
      const char* name = objectGroupElement->Attribute("name");
      drawOrder::Type drawOrder = drawOrderParser::parseFromXmlElement(objectGroupElement);

      size_t objectsSize = 0;
      Object** objectsArray = objectXmlLoader::parseObjectArrayFromXmlElement(
        objectGroupElement,
        objectsSize
      );

      return new ObjectGroup(
        id,
        name ? name : "",
        drawOrder,
        objectsArray,
        objectsSize
      );
    }

    ObjectGroup** parseObjectGroupArrayFromXmlElement(
      XMLElement* parentElement,
      size_t& outObjectGroupCount
    )
    {
      if (parentElement == nullptr)
      {
        outObjectGroupCount = 0;
        return nullptr;
      }

      outObjectGroupCount = static_cast<size_t>(
        parentElement->ChildElementCount("objectgroup")
      );

      if (outObjectGroupCount == 0)
        return nullptr;

      ObjectGroup** objectGroups = new ObjectGroup * [outObjectGroupCount];

      size_t index = 0;
      XMLElement* objectGroupElement = parentElement->FirstChildElement("objectgroup");
      while (objectGroupElement)
      {
        objectGroups[index] = parseObjectGroupFromXmlElement(objectGroupElement);
        objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        ++index;
      }

      return objectGroups;
    }
  }
}