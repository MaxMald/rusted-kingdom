#pragma once

#include <SFML/Window/Mouse.hpp>

#include "rkPrerequisites.h"

namespace rk
{
  class MouseButtonEvent
  {
  public:
    MouseButtonEvent(sf::Mouse::Button button, bool isPressed);
    MouseButtonEvent(const MouseButtonEvent& other);
    MouseButtonEvent(MouseButtonEvent&& other) noexcept;
    ~MouseButtonEvent();

    MouseButtonEvent& operator=(const MouseButtonEvent& other);
    MouseButtonEvent& operator=(MouseButtonEvent&& other) noexcept;
   
    sf::Mouse::Button getButton() const;
    bool isPressed() const;

  private:
    sf::Mouse::Button m_button;
    bool m_isPressed;
  };
}