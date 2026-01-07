#include "rkColliderType.h"

namespace rk
{
  namespace colliderType
  {
    String toString(Type type)
    {
      switch (type)
      {
        case Undefined:
          return "Undefined";
        case Circle:
          return "Circle";
        default:
          return "Unknown";
      }
    }
  }
}