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
      else if (str == "orthogonal")
        return orientation::Type::Orthogonal;
      else
        throw std::runtime_error("Unknown orientation string: " + str);
    }
  }
}