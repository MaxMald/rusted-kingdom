#include "rkIsometricTransformation.h"

namespace rk
{
  namespace isometricTransformation
  {
    Vector2f worldToIsometric(
      float x,
      float y,
      const UInt32& tileHalfWidth,
      const UInt32& tileHalfHeight
    )
    {
      if (tileHalfWidth == 0 || tileHalfHeight == 0)
      {
        throw RuntimeErrorException(
          "rk::isometricTransformation::worldToIsometric: "
          "Tile half width and height must be non-zero."
        );
      }
      return Vector2f(
        (x / tileHalfWidth + y / tileHalfHeight) / 2.0f,
        (y / tileHalfHeight - (x / tileHalfWidth)) / 2.0f
      );
    }

    Vector2f worldToIsometric(
      const sf::Vector2f& cartesianPosition,
      const UInt32& tileHalfWidth,
      const UInt32& tileHalfHeight
    )
    {
      return worldToIsometric(
        cartesianPosition.x,
        cartesianPosition.y,
        tileHalfWidth,
        tileHalfHeight
      );
    }

    Vector2f isometricToWorld(
      float x,
      float y,
      const UInt32& halfWidth,
      const UInt32& halfHeight
    )
    {
      if (halfWidth == 0 || halfHeight == 0)
      {
        throw RuntimeErrorException(
          "rk::isometricTransformation::isometricToWorld: "
          "Tile half width and height must be non-zero."
        );
      }

      return Vector2f(
        (x - y) * halfWidth,
        (x + y) * halfHeight
      );
    }
    Vector2f isometricToWorld(
      const sf::Vector2f& isometricPosition,
      const UInt32& tileHalfWidth,
      const UInt32& tileHalfHeight
    )
    {
      return isometricToWorld(
        isometricPosition.x,
        isometricPosition.y,
        tileHalfWidth,
        tileHalfHeight
      );
    }
  }
}