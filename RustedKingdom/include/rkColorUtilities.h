#pragma once

#include <SFML/Graphics/Color.hpp>
#include "rkPrerequisites.h"

namespace rk
{
  namespace colorUtilities
  {
    sf::Color getColorFromHex(const String& hexColor);
  }
}