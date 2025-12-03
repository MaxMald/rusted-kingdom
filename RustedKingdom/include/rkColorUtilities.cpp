#include "rkColorUtilities.h"

#include <sstream>
#include <iomanip>

namespace rk
{
  namespace colorUtilities
  {
    sf::Color getColorFromHex(const String& hexColor)
    {
      String value = hexColor;
      if (value[0] == '#')
        value = value.substr(1);

      // Default alpha is 255
      UInt8 r = 0, g = 0, b = 0, a = 255;

      if (value.length() == 8)
      {
        a = static_cast<UInt8>(std::stoi(value.substr(0, 2), nullptr, 16));
        r = static_cast<UInt8>(std::stoi(value.substr(2, 2), nullptr, 16));
        g = static_cast<UInt8>(std::stoi(value.substr(4, 2), nullptr, 16));
        b = static_cast<UInt8>(std::stoi(value.substr(6, 2), nullptr, 16));
      }

      return sf::Color(r, g, b, a);
    }
  }
}