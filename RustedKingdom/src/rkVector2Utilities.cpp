#include "rkVector2Utilities.h"

namespace rk
{
  namespace vector2Utilities
  {
    Vector2f truncated(const Vector2f& vector, const float& maxLength)
    {
      if (vector.length() > maxLength)
        return vector.normalized() * maxLength;
      return vector;
    }
  }
}