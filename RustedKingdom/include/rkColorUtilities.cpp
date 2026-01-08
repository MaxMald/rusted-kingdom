#include "rkColorUtilities.h"

#include <sstream>
#include <iomanip>

namespace rk
{
  namespace colorUtilities
  {
    sf::Color getColorFromTiledHex(const String& hexColor)
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

    sf::Color getColorFromHex(const String& hexColor)
    {
      String value = hexColor;
      if (value[0] == '#')
        value = value.substr(1);

      // Default alpha is 255
      UInt8 r = 0, g = 0, b = 0, a = 255;

      if (value.length() == 8)
      {
        r = static_cast<UInt8>(std::stoi(value.substr(0, 2), nullptr, 16));
        g = static_cast<UInt8>(std::stoi(value.substr(2, 2), nullptr, 16));
        b = static_cast<UInt8>(std::stoi(value.substr(4, 2), nullptr, 16));
        a = static_cast<UInt8>(std::stoi(value.substr(6, 2), nullptr, 16));
      }

      return sf::Color(r, g, b, a);
    }

    ImVec4 getImVec4FromColor(const sf::Color& color)
    {
      return ImVec4(
        static_cast<float>(color.r) / 255.0f,
        static_cast<float>(color.g) / 255.0f,
        static_cast<float>(color.b) / 255.0f,
        static_cast<float>(color.a) / 255.0f
      );
    }

    sf::Color getColorFromImVec4(const ImVec4& color)
    {
      return sf::Color(
        static_cast<UInt8>(color.x * 255.0f),
        static_cast<UInt8>(color.y * 255.0f),
        static_cast<UInt8>(color.z * 255.0f),
        static_cast<UInt8>(color.w * 255.0f)
      );
    }
  }
}