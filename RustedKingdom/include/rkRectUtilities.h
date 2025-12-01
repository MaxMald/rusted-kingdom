#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "rkPrerequisites.h"

using sf::FloatRect;

namespace rk
{
  namespace rectUtilities
  {
    FloatRect unify(const FloatRect& a, const FloatRect& b);
  }
}