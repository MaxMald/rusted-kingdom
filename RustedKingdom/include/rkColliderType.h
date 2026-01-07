#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  namespace colliderType
  {
    enum Type : UInt8
    {
      Undefined = 0,
      Circle = 1
    };

    String toString(Type type);
  }
}