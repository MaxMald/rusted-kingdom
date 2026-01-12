#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"

using sf::Vector2f;

namespace rk
{
  namespace vector2Utilities
  {
    Vector2f truncated(const Vector2f& vector, const float& maxLength);    
  }
}