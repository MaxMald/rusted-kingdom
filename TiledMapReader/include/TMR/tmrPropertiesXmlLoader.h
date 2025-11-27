#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tinyxml2
{
  class XMLElement;
}

using tinyxml2::XMLElement;

namespace tmr
{
  class Properties;
  class Property;
  class BoolProperty;
  class ColorProperty;
  class FileProperty;
  class FloatProperty;
  class IntProperty;
  class ObjectProperty;
  class StringProperty;

  namespace propertiesXmlLoader
  {
    Properties* loadProperties(XMLElement* propertiesElement);
    Property* loadProperty(XMLElement* propertyElement);
    BoolProperty* loadBoolProperty(XMLElement* propertyElement, const char* name);
    ColorProperty* loadColorProperty(XMLElement* propertyElement, const char* name);
    FileProperty* loadFileProperty(XMLElement* propertyElement, const char* name);
    FloatProperty* loadFloatProperty(XMLElement* propertyElement, const char* name);
    IntProperty* loadIntProperty(XMLElement* propertyElement, const char* name);
    ObjectProperty* loadObjectProperty(XMLElement* propertyElement, const char* name);
    StringProperty* loadStringProperty(XMLElement* propertyElement, const char* name);
  }
}