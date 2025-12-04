#include "rkMouseButtonEvent.h"

namespace rk
{
  MouseButtonEvent::MouseButtonEvent(sf::Mouse::Button button, bool isPressed) :
    m_button(button),
    m_isPressed(isPressed)
  {
  }

  MouseButtonEvent::MouseButtonEvent(const MouseButtonEvent& other) :
    m_button(other.m_button),
    m_isPressed(other.m_isPressed)
  {
  }

  MouseButtonEvent::MouseButtonEvent(MouseButtonEvent&& other) noexcept :
    m_button(other.m_button),
    m_isPressed(other.m_isPressed)
  {
  }

  MouseButtonEvent::~MouseButtonEvent()
  {
  }

  MouseButtonEvent& MouseButtonEvent::operator=(const MouseButtonEvent& other)
  {
    if (this != &other)
    {
      m_button = other.m_button;
      m_isPressed = other.m_isPressed;
    }
    return *this;
  }

  MouseButtonEvent& MouseButtonEvent::operator=(MouseButtonEvent&& other) noexcept
  {
    if (this != &other)
    {
      m_button = other.m_button;
      m_isPressed = other.m_isPressed;
    }
    return *this;
  }

  sf::Mouse::Button MouseButtonEvent::getButton() const
  {
    return sf::Mouse::Button();
  }

  bool MouseButtonEvent::isPressed() const
  {
    return false;
  }
}