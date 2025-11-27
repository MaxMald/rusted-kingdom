#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  namespace propertyType
  {
    enum Type : uint8_t
    {
      Undefined = 0,
      Color = 1,
      File = 2,
      Float = 3,
      Int = 4,
      Bool = 5,
      Object = 6,
      String = 7
    };
  }
}