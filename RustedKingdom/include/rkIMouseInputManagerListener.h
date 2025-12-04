#pragma once

#include "rkPrerequisites.h"
#include "rkMouseButtonEvent.h"

namespace rk
{
  class IMouseInputManagerListener
  {
  public:
    virtual ~IMouseInputManagerListener() = default;

    virtual void onMouseButtonPressed(const MouseButtonEvent&) = 0;
    virtual void onMouseButtonReleased(const MouseButtonEvent&) = 0;
  };
}