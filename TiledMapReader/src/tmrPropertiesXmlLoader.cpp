#include "TMR/tmrPropertiesXmlLoader.h"

#include <string>
#include <vector>

#include "TMR/tinyxml2.h"
#include "TMR/tmrProperties.h"
#include "TMR/tmrBoolProperty.h"
#include "TMR/tmrColorProperty.h"
#include "TMR/tmrFileProperty.h"
#include "TMR/tmrFloatProperty.h"
#include "TMR/tmrIntProperty.h"
#include "TMR/tmrObjectProperty.h"
#include "TMR/tmrStringProperty.h"

using namespace tinyxml2;
using std::vector;
using std::string;

namespace tmr
{
  namespace propertiesXmlLoader
  {
    Properties* loadProperties(XMLElement* propertiesElement)
    {
      if (propertiesElement == nullptr)
        return new Properties(nullptr, 0);

      vector<Property*> properties;
      XMLElement* nextProperty = propertiesElement->FirstChildElement("property");
      while (nextProperty)
      {
        Property* property = loadProperty(nextProperty);
        if (property)
          properties.push_back(property);

        nextProperty = nextProperty->NextSiblingElement("property");
      }

      if (properties.size() > 0)
      {
        size_t propertiesCount = properties.size();
        Property** propertiesArray = new Property*[propertiesCount];
        for (size_t i = 0; i < propertiesCount; ++i)
          propertiesArray[i] = properties[i];

        return new Properties(propertiesArray, propertiesCount);
      }

      return new Properties(nullptr, 0);
    }

    Property* loadProperty(XMLElement* propertyElement)
    {
      if (propertyElement == nullptr)
        return nullptr;

      const char* name = propertyElement->Attribute("name");
      const char* typeAttr = propertyElement->Attribute("type");
      string type = typeAttr ? typeAttr : "string";

      if (type == "bool")
        return loadBoolProperty(propertyElement, name);
      else if (type == "color")
        return loadColorProperty(propertyElement, name);
      else if (type == "file")
        return loadFileProperty(propertyElement, name);
      else if (type == "float")
        return loadFloatProperty(propertyElement, name);
      else if (type == "int")
        return loadIntProperty(propertyElement, name);
      else if (type == "object")
        return loadObjectProperty(propertyElement, name);
      else // string type
        return loadStringProperty(propertyElement, name);
    }

    BoolProperty* loadBoolProperty(
      XMLElement* propertyElement,
      const char* name
    )
    {
      bool value = propertyElement->BoolAttribute("value", false);
      return new BoolProperty(name ? name : "", value);
    }

    ColorProperty* loadColorProperty(
      XMLElement* propertyElement,
      const char* name
    )
    {
      const char* value = propertyElement->Attribute("value");
      return new ColorProperty(name ? name : "", value ? value : "");
    }

    FileProperty* loadFileProperty(
      XMLElement* propertyElement,
      const char* name
    )
    {
      const char* value = propertyElement->Attribute("value");
      return new FileProperty(name ? name : "", value ? value : "");
    }

    FloatProperty* loadFloatProperty(
      XMLElement* propertyElement,
      const char* name
    )
    {
      float value = propertyElement->FloatAttribute("value", 0.0f);
      return new FloatProperty(name ? name : "", value);
    }

    IntProperty* loadIntProperty(
      XMLElement* propertyElement,
      const char* name
    )
    {
      int32_t value = propertyElement->IntAttribute("value", 0);
      return new IntProperty(name ? name : "", value);
    }

    ObjectProperty* loadObjectProperty(
      XMLElement* propertyElement,
      const char* name
    )
    {
      int32_t value = propertyElement->IntAttribute("value", 0);
      return new ObjectProperty(name ? name : "", value);
    }

    StringProperty* loadStringProperty(
      XMLElement* propertyElement,
      const char* name
    )
    {
      const char* value = propertyElement->Attribute("value");
      return new StringProperty(name ? name : "", value ? value : "");
    }
  }
}