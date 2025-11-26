#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  namespace objectType
  {
    enum Type : std::uint8_t
    {
      Undefined = 0,
      TileReference = 1,
      Ellipse = 2
    };
  }
}