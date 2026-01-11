#include "rkRigidBodyType.h"

namespace rk
{
  namespace rigidBodyType
  {
    String toString(Type type)
    {
      switch (type)
      {
        case Undefined:
          return "Undefined";
        case Static:
          return "Static";
        case Kinematic:
          return "Kinematic";
        default:
          return "Unknown";
      }
    }
  }
}