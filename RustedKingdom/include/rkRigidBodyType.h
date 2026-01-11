#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  namespace rigidBodyType
  {
    enum Type : UInt8
    {
      Undefined = 0,
      Static = 1,
      Kinematic = 2
    };

    String toString(Type type);
  }
}