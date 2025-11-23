#include "TMR/tmrRenderOrderParser.h"

#include <string>
#include <stdexcept>

#include "TMR/tinyxml2.h"

using namespace tinyxml2;

namespace tmr
{
  namespace renderOrderParser
  {
    renderOrder::Type parseFromXmlElement(XMLElement* element)
    {
      if(!element)
        return renderOrder::Type::Undefined;

      const char* renderOrderStr = element->Attribute("renderorder");
      return parseFromString(renderOrderStr);
    }

    renderOrder::Type parseFromString(const char* str)
    {
      if(!str)
        return renderOrder::Type::Undefined;

      std::string renderOrderStr(str);

      if(renderOrderStr == "right-down")
        return renderOrder::Type::RightDown;
      else if(renderOrderStr == "right-up")
        return renderOrder::Type::RightUp;
      else if(renderOrderStr == "left-down")
        return renderOrder::Type::LeftDown;
      else if(renderOrderStr == "left-up")
        return renderOrder::Type::LeftUp;
      else
        throw std::runtime_error("Unknown render order string: " + renderOrderStr);
    }
  }
}