#pragma once

#include "rkVector2Utilities.h"

namespace rk
{
  namespace steerForces
  {
    Vector2f seek(
      const sf::Vector2f& currentPosition,
      const sf::Vector2f& targetPosition,
      const sf::Vector2f& currentVelocity,
      const float& maxSpeed
    );
  }
}