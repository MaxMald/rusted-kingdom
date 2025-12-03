#include "rkWindowManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace rk
{
  WindowManager::WindowManager()
    : m_renderWindow(nullptr)
  {
  }

  WindowManager::~WindowManager()
  {
  }

  RenderWindow& WindowManager::getRenderWindow()
  {
    if (!m_renderWindow)
      throw RuntimeErrorException("Render window is not created.");
    return *m_renderWindow;
  }

  const RenderWindow& WindowManager::getRenderWindow() const
  {
    if (!m_renderWindow)
      throw RuntimeErrorException("Render window is not created.");
    return *m_renderWindow;
  }

  void WindowManager::init(ServiceLocator&)
  {
    // Initialize the render window
  }

  void WindowManager::destroy()
  {
    if (m_renderWindow)
    {
      delete m_renderWindow;
      m_renderWindow = nullptr;
    }
  }

  void WindowManager::createWindow()
  {
    m_renderWindow = new RenderWindow(
      sf::VideoMode({ 1920, 1080 }),
      "Rusted Kingdom",
      sf::Style::Default,
      sf::State::Fullscreen
    );

    if (!m_renderWindow->isOpen())
    {
      delete m_renderWindow;

      throw RuntimeErrorException(
        "Failed to create RenderWindow."
      );
    }
  }
}