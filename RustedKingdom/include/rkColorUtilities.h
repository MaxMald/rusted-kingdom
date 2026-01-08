#pragma once

#include <SFML/Graphics/Color.hpp>
#include "rkPrerequisites.h"
#include "imgui.h"

namespace rk
{
  namespace colorUtilities
  {
    sf::Color getColorFromTiledHex(const String& hexColor);
    sf::Color getColorFromHex(const String& hexColor);
    ImVec4 getImVec4FromColor(const sf::Color& color);
    sf::Color getColorFromImVec4(const ImVec4& color);
  }
}