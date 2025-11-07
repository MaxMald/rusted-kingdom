#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"

namespace tmr
{
  class Object;

  class ObjectParser
  {
  public:
    ObjectParser();
    ~ObjectParser();

    Object* parseFromJson(const Json& json);
  };
}