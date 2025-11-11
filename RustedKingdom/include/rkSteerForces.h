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
    )
    {
      sf::Vector2f desiredVelocity = targetPosition - currentPosition;
      desiredVelocity = vector2Utilities::truncated(desiredVelocity, maxSpeed);

      sf::Vector2f steering = desiredVelocity - currentVelocity;
      return vector2Utilities::truncated(steering, maxSpeed);
    }
  }
}