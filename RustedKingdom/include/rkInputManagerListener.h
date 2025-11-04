#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class InputManagerListener
  {
  public:
    virtual ~InputManagerListener() = default;
    virtual void onInputEvent(const rk::InputEvent& event) = 0;
  };
}