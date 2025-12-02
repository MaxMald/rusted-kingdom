#include "TMR/tmrObjectXmlLoader.h"

#include "TMR/tinyxml2.h"
#include "TMR/tmrTileReferenceObject.h"
#include "TMR/tmrEllipseObject.h"
#include "TMR/tmrPropertiesXmlLoader.h"

using namespace tinyxml2;

namespace tmr
{
  namespace objectXmlLoader
  {
    static bool isTileReference(XMLElement* element);
    static bool isEllipse(XMLElement* element);

    static Object* parseTileReference(
      XMLElement* objectElement,
      uint32_t id,
      float x, float y,
      bool visible,
      const char* name,
      const char* type,
      Properties* properties
    );

    static Object* parseEllipse(
      XMLElement* objectElement,
      uint32_t id,
      float x, float y,
      bool visible,
      const char* name,
      const char* type,
      Properties* properties
    );
  }
}

namespace tmr
{
  namespace objectXmlLoader
  {
    Object* parseObjectFromXmlElement(XMLElement* objectElement)
    {
      if (objectElement == nullptr)
        return nullptr;

      uint32_t id = objectElement->UnsignedAttribute("id", 0);
      float x = objectElement->FloatAttribute("x", 0.0f);
      float y = objectElement->FloatAttribute("y", 0.0f);
      bool visible = objectElement->BoolAttribute("visible", true);
      const char* name = objectElement->Attribute("name");
      const char* type = objectElement->Attribute("type");
      Properties* properties = propertiesXmlLoader::loadProperties(
        objectElement->FirstChildElement("properties")
      );

      if (isTileReference(objectElement))
      {
        return parseTileReference(
          objectElement,
          id,
          x, y,
          visible,
          name,
          type,
          properties
        );
      }
      else if (isEllipse(objectElement))
      {
        return parseEllipse(
          objectElement,
          id,
          x, y,
          visible,
          name,
          type,
          properties
        );
      }

      return new Object(
        objectType::Undefined,
        id,
        x, y,
        visible,
        name ? name : "",
        type ? type : "",
        properties
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

    static bool isTileReference(XMLElement* element)
    {
      return (element->Attribute("gid") != nullptr);
    }

    static bool isEllipse(XMLElement* element)
    {
      return (element->FirstChildElement("ellipse") != nullptr);
    }

    static Object* parseTileReference(
      XMLElement* objectElement,
      uint32_t id,
      float x, float y,
      bool visible,
      const char* name,
      const char* type,
      Properties* properties
    )
    {
      uint32_t gid = objectElement->UnsignedAttribute("gid", 0);
      uint32_t height = objectElement->UnsignedAttribute("height", 0);
      uint32_t width = objectElement->UnsignedAttribute("width", 0);
      float rotation = objectElement->FloatAttribute("rotation", 0.0f);

      return new TileReferenceObject(
        gid, id,
        width, height,
        visible,
        rotation,
        x, y,
        name ? name : "",
        type ? type : "",
        properties
      );
    }

    static Object* parseEllipse(
      XMLElement* objectElement,
      uint32_t id,
      float x, float y,
      bool visible,
      const char* name,
      const char* type,
      Properties* properties
    )
    {
      uint32_t height = objectElement->UnsignedAttribute("height", 0);
      uint32_t width = objectElement->UnsignedAttribute("width", 0);

      return new EllipseObject(
        id,
        width, height,
        visible,
        x, y,
        name ? name : "",
        type ? type : "",
        properties
      );
    }
  }
}