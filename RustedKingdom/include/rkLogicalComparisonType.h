#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  namespace logicalComparisonType
  {
    enum Type : UInt8
    {
      Undefined,
      Less,
      LessEqual,
      Equal,
      NotEqual,
      GreaterEqual,
      Greater
    };
  }
}