#include "TMR/tmrOrientationParser.h"
#include <string>
#include <stdexcept>

namespace tmr
{
  namespace orientationParser
  {
    orientation::Type parseFromString(
      const char* orientationStr
    )
    {
      if (!orientationStr)
        throw std::runtime_error("orientationStr is null");

      std::string str(orientationStr);

      if (str == "isometric")
        return orientation::Type::Isometric;

      throw std::runtime_error("Unknown orientation string: " + str);
    }
  }
}