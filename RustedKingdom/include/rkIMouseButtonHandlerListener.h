#pragma once

#include <SFML/Window/Mouse.hpp>

#include "rkPrerequisites.h"

namespace rk
{
  class IMouseButtonHandlerListener
  {
  public:
    virtual ~IMouseButtonHandlerListener() = default;

    virtual void onMouseButtonPressed(sf::Mouse::Button button) = 0;
    virtual void onMouseButtonReleased(sf::Mouse::Button button) = 0;
  };
}