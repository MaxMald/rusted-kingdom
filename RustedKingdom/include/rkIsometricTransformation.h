#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"

using sf::Vector2f;

namespace rk
{
  namespace isometricTransformation
  {
    Vector2f worldToIsometric(
      float x,
      float y,
      const UInt32& tileHalfWidth,
      const UInt32& tileHalfHeight
    );

    Vector2f worldToIsometric(
      const sf::Vector2f& cartesianPosition,
      const UInt32& tileHalfWidth,
      const UInt32& tileHalfHeight
    );

    Vector2f isometricToWorld(
      float x,
      float y,
      const UInt32& tileHalfWidth,
      const UInt32& tileHalfHeight
    );

    Vector2f isometricToWorld(
      const sf::Vector2f& isometricPosition,
      const UInt32& tileHalfWidth,
      const UInt32& tileHalfHeight
    );
  }
}