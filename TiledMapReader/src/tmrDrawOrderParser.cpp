#include "TMR/tmrDrawOrderParser.h"

#include <string>
#include <stdexcept>

#include "TMR/tinyxml2.h"

using namespace tinyxml2;

namespace tmr
{
  namespace drawOrderParser
  {
    drawOrder::Type parseFromXmlElement(XMLElement* element)
    {
      if(!element)
        return drawOrder::Type::Undefined;

      const char* drawOrderStr = element->Attribute("draworder");
      return parseFromString(drawOrderStr);
    }

    drawOrder::Type parseFromString(const char* str)
    {
      if(!str)
        return drawOrder::Type::Undefined;

      std::string drawOrderStr(str);

      if(drawOrderStr == "topdown")
        return drawOrder::Type::TopDown;
      else if(drawOrderStr == "index")
        return drawOrder::Type::Index;
      else
        throw std::runtime_error("Unknown draw order string: " + drawOrderStr);
    }
  }
}