#include "rkRectUtilities.h"

using sf::Vector2f;

namespace rk
{
  namespace rectUtilities
  {
    FloatRect unify(const FloatRect& a, const FloatRect& b)
    {
      float left = std::min(a.position.x, b.position.x);
      float top = std::min(a.position.y, b.position.y);
      float right = std::max(a.position.x + a.size.x, b.position.x + b.size.x);
      float bottom = std::max(a.position.y + a.size.y, b.position.y + b.size.y);

      return FloatRect(
        Vector2f(left, top),
        Vector2f(right - left, bottom - top)
      );
    }
  }
}