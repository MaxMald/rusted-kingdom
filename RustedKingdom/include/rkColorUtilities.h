#pragma once

#include <SFML/Graphics/Color.hpp>
#include "rkPrerequisites.h"

namespace rk
{
  namespace colorUtilities
  {
    sf::Color getColorFromTiledHex(const String& hexColor);
    sf::Color getColorFromHex(const String& hexColor);
  }
}