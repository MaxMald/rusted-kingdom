#include "rkMouseButtonEvent.h"

namespace rk
{
  MouseButtonEvent::MouseButtonEvent(sf::Mouse::Button button, bool isPressed) :
    m_button(button),
    m_isPressed(isPressed),
    m_isConsumed(false)
  {
  }

  MouseButtonEvent::MouseButtonEvent(const MouseButtonEvent& other) :
    m_button(other.m_button),
    m_isPressed(other.m_isPressed),
    m_isConsumed(other.m_isConsumed)
  {
  }

  MouseButtonEvent::MouseButtonEvent(MouseButtonEvent&& other) noexcept :
    m_button(other.m_button),
    m_isPressed(other.m_isPressed),
    m_isConsumed(other.m_isConsumed)
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
      m_isConsumed = other.m_isConsumed;
    }
    return *this;
  }

  MouseButtonEvent& MouseButtonEvent::operator=(MouseButtonEvent&& other) noexcept
  {
    if (this != &other)
    {
      m_button = other.m_button;
      m_isPressed = other.m_isPressed;
      m_isConsumed = other.m_isConsumed;
    }
    return *this;
  }

  sf::Mouse::Button MouseButtonEvent::getButton() const
  {
    return m_button;
  }

  bool MouseButtonEvent::isPressed() const
  {
    return m_isPressed;
  }

  void MouseButtonEvent::setConsumed(bool consumed)
  {
    m_isConsumed = consumed;
  }

  bool MouseButtonEvent::isConsumed() const
  {
    return m_isConsumed;
  }
}