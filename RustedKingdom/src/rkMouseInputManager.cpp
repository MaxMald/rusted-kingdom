#include "rkMouseInputManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "rkMouseButtonHandler.h"
#include "rkWindowManager.h"
#include "rkIMouseInputManagerListener.h"
#include "rkMouseButtonEvent.h"

namespace rk
{
  MouseInputManager::MouseInputManager() : 
    m_listeners(),
    m_buttonHandlers(),
    m_windowManager(nullptr)
  {
  }

  MouseInputManager::~MouseInputManager()
  {
  }

  Vector2i MouseInputManager::getMousePosition() const
  {
    return sf::Mouse::getPosition();
  }

  Vector2i MouseInputManager::getMousePositionRelativeToWindow(
  ) const
  {
    return sf::Mouse::getPosition(m_windowManager->getRenderWindow());
  }

  bool MouseInputManager::isButtonPressed(sf::Mouse::Button button) const
  {
    auto it = m_buttonHandlers.find(button);
    if (it != m_buttonHandlers.end())
      return it->second->isButtonPressed();

    return false;
  }

  void MouseInputManager::onMouseButtonPressed(sf::Mouse::Button button)
  {
    MouseButtonEvent event(button, true);
    for (auto* listener : m_listeners)
      listener->onMouseButtonPressed(event);
  }

  void MouseInputManager::onMouseButtonReleased(sf::Mouse::Button button)
  {
    MouseButtonEvent event(button, false);
    for (auto* listener : m_listeners)
      listener->onMouseButtonReleased(event);
  }

  void MouseInputManager::prepare(SharedPtr<WindowManager> windowManager)
  {
    m_windowManager = windowManager;
    registerButtonHandlers();
  }

  void MouseInputManager::update()
  {
    for (auto& [button, handler] : m_buttonHandlers)
      handler->update();
  }

  void MouseInputManager::subscribe(IMouseInputManagerListener* listener)
  {
    m_listeners.push_back(listener);
  }

  void MouseInputManager::unsubscribe(IMouseInputManagerListener* listener)
  {
    m_listeners.erase(
      std::remove(m_listeners.begin(), m_listeners.end(), listener),
      m_listeners.end()
    );
  }

  void MouseInputManager::registerButtonHandlers()
  {
    for (int button = 0; button < sf::Mouse::ButtonCount; ++button)
    {
      sf::Mouse::Button btn = static_cast<sf::Mouse::Button>(button);
      m_buttonHandlers[btn] = MakeShared<MouseButtonHandler>(btn);
      m_buttonHandlers[btn]->subscribe(this);
    }
  }
}