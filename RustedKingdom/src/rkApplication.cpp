#include "rkApplication.h"

#include <iostream>

#include "rkScenesManager.h"
#include "rkWindowManager.h"

using std::optional;
using sf::Time;
using sf::RenderStates;
using sf::Clock;

namespace rk
{
  Application::Application() :
    m_scenesManager(nullptr),
    m_windowManager(nullptr),
    m_serviceLocator()
  {
  }

  Application::~Application()
  {
  }

  void Application::prepare()
  {
    registerServices();

    m_scenesManager =
      m_serviceLocator.getService<ScenesManager>();
    m_windowManager =
      m_serviceLocator.getService<WindowManager>();

    m_windowManager->createWindow();
    m_serviceLocator.initializeServices();
  }

  void Application::run()
  {
    RenderWindow& renderWindow = m_windowManager->getRenderWindow();

    Clock deltaClock;
    while (renderWindow.isOpen())
    {
      while (const optional event = renderWindow.pollEvent())
      {
        if (event->is<sf::Event::Closed>())
          renderWindow.close();
      }

      try
      {
        update(deltaClock.restart().asSeconds());
        draw(renderWindow);
      }
      catch (const std::exception& ex)
      {
        std::cerr << "Exception in main loop: " << ex.what() << std::endl;
        renderWindow.close();
      }
      catch (...)
      {
        std::cerr << "Unknown exception in main loop." << std::endl;
        renderWindow.close();
      }
    }
  }

  void Application::destroy()
  {
    m_serviceLocator.destroy();
  }

  void Application::update(float deltaTime)
  {
    m_scenesManager->update(deltaTime);
  }

  void Application::draw(RenderWindow& renderWindow)
  {
    renderWindow.clear(sf::Color::Black);
    m_scenesManager->draw(renderWindow, RenderStates::Default);
    renderWindow.display();
  }

  void Application::registerServices()
  {
    m_serviceLocator.registerService(MakeShared<ScenesManager>());
    m_serviceLocator.registerService(MakeShared<WindowManager>());
  }
}