#include "rkMouseButtonHandler.h"
#include "rkIMouseButtonHandlerListener.h"

namespace rk
{
  MouseButtonHandler::MouseButtonHandler(sf::Mouse::Button button)
    : m_isPressed(false)
    , m_button(button)
  {
  }

  MouseButtonHandler::~MouseButtonHandler()
  {
  }

  sf::Mouse::Button MouseButtonHandler::getButtonType() const
  {
    return m_button;
  }

  void MouseButtonHandler::subscribe(IMouseButtonHandlerListener* listener)
  {
    m_listeners.push_back(listener);
  }

  void MouseButtonHandler::unsubscribe(IMouseButtonHandlerListener* listener)
  {
    m_listeners.erase(
      std::remove(m_listeners.begin(), m_listeners.end(), listener),
      m_listeners.end()
    );
  }

  bool MouseButtonHandler::isButtonPressed() const
  {
    return m_isPressed;
  }

  void MouseButtonHandler::update()
  {
    bool currentlyPressed = sf::Mouse::isButtonPressed(m_button);
    if (currentlyPressed && !m_isPressed)
    {
      m_isPressed = true;
      for (auto* listener : m_listeners)
        listener->onMouseButtonPressed(m_button);
    }
    else if (!currentlyPressed && m_isPressed)
    {
      m_isPressed = false;
      for (auto* listener : m_listeners)
        listener->onMouseButtonReleased(m_button);
    }
  }
}