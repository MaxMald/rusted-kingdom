#pragma once

#include "TMR/tmrDrawOrder.h"

namespace tmr
{
  namespace drawOrderParser
  {
    drawOrder::Type parseFromString(const char* str);
  }
}