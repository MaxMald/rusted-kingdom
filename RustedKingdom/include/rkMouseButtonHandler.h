#pragma once

#include <SFML/Window/Mouse.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class IMouseButtonHandlerListener;

  class MouseButtonHandler : public NonCopyable
  {
  public:
    MouseButtonHandler(sf::Mouse::Button);
    ~MouseButtonHandler();

    sf::Mouse::Button getButtonType() const;
    void subscribe(IMouseButtonHandlerListener*);
    void unsubscribe(IMouseButtonHandlerListener*);
    bool isButtonPressed() const;
    void update();

  private:
    bool m_isPressed;
    sf::Mouse::Button m_button;
    Vector<IMouseButtonHandlerListener*> m_listeners;
  };
}