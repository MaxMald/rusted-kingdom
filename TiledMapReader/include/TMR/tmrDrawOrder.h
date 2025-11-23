#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  namespace drawOrder
  {
    enum Type : std::uint8_t
    {
      Undefined = 0,
      TopDown = 1,
      Index = 2
    };
  }
}