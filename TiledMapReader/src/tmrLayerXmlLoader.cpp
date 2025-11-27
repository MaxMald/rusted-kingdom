#include "TMR/tmrLayerXmlLoader.h"

#include <string>

#include "TMR/tinyxml2.h"
#include "TMR/tmrGridDataLayer.h"
#include "TMR/tmrObjectGroupLayer.h"
#include "TMR/tmrObjectGroupXmlLoader.h"
#include "TMR/tmrGridDataLayerXmlLoader.h"
#include "TMR/tmrPropertiesXmlLoader.h"

using namespace tinyxml2;
using std::string;

namespace tmr
{
  namespace layerXmlLoader
  {
    static Layer* parseObjectGroupLayerFromXmlElement(XMLElement* layerElement)
    {
      const char* name = layerElement->Attribute("name");
      int32_t id = layerElement->IntAttribute("id", 0);
      ObjectGroup* objectGroup = objectGroupXmlLoader::parseObjectGroupFromXmlElement(
        layerElement
      );

      if (objectGroup == nullptr)
        return nullptr;

      Properties* properties = propertiesXmlLoader::loadProperties(
        layerElement->FirstChildElement("properties")
      );

      return new ObjectGroupLayer(id, name ? name : "", properties, objectGroup);
    }

    Layer* parseLayerFromXmlElement(XMLElement* layerElement)
    {
      if (!layerElement)
        return nullptr;
      
      string tag = layerElement->Name();
      if (tag == "layer")
      {
        return gridDataLayerXmlLoader::parseLayerFromXmlElement(layerElement);
      }
      else if (tag == "objectgroup")
      {
        return parseObjectGroupLayerFromXmlElement(layerElement);
      }
      else
      {
        return nullptr;
      }
    }

    bool isLayerXmlElement(XMLElement* element)
    {
      if (!element)
        return false;

      string tag = element->Name();
      return (tag == "layer" || tag == "objectgroup");
    }
  }
}