#include "TMR/tmrOrientationParser.h"

#include <string>
#include <stdexcept>

#include "TMR/tinyxml2.h"

using namespace tinyxml2;

namespace tmr
{
  namespace orientationParser
  {
    orientation::Type parseFromXmlElement(XMLElement* element)
    {
      if (!element)
        return orientation::Type::Undefined;

      const char* orientationStr = element->Attribute("orientation");
      return parseFromString(orientationStr);
    }

    orientation::Type parseFromString(
      const char* orientationStr
    )
    {
      if (!orientationStr)
        return orientation::Type::Undefined;

      std::string str(orientationStr);

      if (str == "isometric")
        return orientation::Type::Isometric;
      else if (str == "orthogonal")
        return orientation::Type::Orthogonal;
      else
        throw std::runtime_error("Unknown orientation string: " + str);
    }
  }
}