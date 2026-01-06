#include "rkArmyControlType.h"

namespace rk
{
  namespace armyControlType
  {
    String toString(Type controlType)
    {
      switch (controlType)
      {
        case User:
          return "User";
        case AI:
          return "AI";
        default:
          return "Unknown";
      }
    }
  }
}