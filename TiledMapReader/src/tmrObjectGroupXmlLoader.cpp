#include "TMR/tmrObjectGroupXmlLoader.h"

#include <vector>

#include "TMR/tinyxml2.h"
#include "TMR/tmrObjectGroup.h"
#include "TMR/tmrObject.h"
#include "TMR/tmrDrawOrderParser.h"

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
      Object** objectsArray = parseObjectArrayFromXmlElement(
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

    Object* parseObjectFromXmlElement(XMLElement* objectElement)
    {
      if (objectElement == nullptr)
        return nullptr;

      uint32_t gid = objectElement->UnsignedAttribute("gid", 0);
      uint32_t id = objectElement->UnsignedAttribute("id", 0);
      uint32_t height = objectElement->UnsignedAttribute("height", 0);
      uint32_t width = objectElement->UnsignedAttribute("width", 0);
      bool visible = objectElement->BoolAttribute("visible", true);
      bool ellipse = (objectElement->FirstChildElement("ellipse") != nullptr);
      float rotation = objectElement->FloatAttribute("rotation", 0.0f);
      float x = objectElement->FloatAttribute("x", 0.0f);
      float y = objectElement->FloatAttribute("y", 0.0f);
      const char* name = objectElement->Attribute("name");
      const char* type = objectElement->Attribute("type");

      return new Object(
        gid,
        id,
        height,
        width,
        visible,
        ellipse,
        rotation,
        x,
        y,
        name ? name : "",
        type ? type : ""
      );
    }

    Object** parseObjectArrayFromXmlElement(
      XMLElement* parentElement,
      size_t& outObjectCount
    )
    {
      if (parentElement == nullptr)
      {
        outObjectCount = 0;
        return nullptr;
      }

      outObjectCount = static_cast<size_t>(
        parentElement->ChildElementCount("object")
      );

      if (outObjectCount == 0)
        return nullptr;

      Object** objects = new Object * [outObjectCount];

      size_t index = 0;
      XMLElement* objectElement = parentElement->FirstChildElement("object");
      while (objectElement)
      {
        objects[index] = parseObjectFromXmlElement(objectElement);
        objectElement = objectElement->NextSiblingElement("object");
        ++index;
      }

      return objects;
    }
  }
}