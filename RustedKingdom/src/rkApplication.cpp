#include "rkApplication.h"

#include <iostream>

#include "rkScenesManager.h"

using std::optional;
using sf::Time;
using sf::RenderStates;
using sf::Clock;

namespace rk
{
  Application::Application() :
    m_window(nullptr),
    m_scenesManager(nullptr),
    m_serviceLocator()
  {
  }

  Application::~Application()
  {
  }

  void Application::prepare()
  {
    createWindow();
    registerServices();
    m_serviceLocator.initializeServices();

    m_scenesManager = 
      m_serviceLocator.getService<ScenesManager>();
  }

  void Application::run()
  {
    if (!m_window)
      return;

    Clock deltaClock;
    while (m_window->isOpen())
    {
      while (const optional event = m_window->pollEvent())
      {
        if (event->is<sf::Event::Closed>())
          m_window->close();
      }

      try
      {
        update(deltaClock.restart().asSeconds());
        draw();
      }
      catch (const std::exception& ex)
      {
        std::cerr << "Exception in main loop: " << ex.what() << std::endl;
        m_window->close();
      }
      catch (...)
      {
        std::cerr << "Unknown exception in main loop." << std::endl;
        m_window->close();
      }
    }
  }

  void Application::destroy()
  {
    m_serviceLocator.destroy();

    if (m_window)
      delete m_window;
  }

  void Application::update(float deltaTime)
  {
    m_scenesManager->update(deltaTime);
  }

  void Application::draw()
  {
    m_window->clear(sf::Color::Black);
    m_scenesManager->draw(*m_window, RenderStates::Default);
    m_window->display();
  }

  void Application::createWindow()
  {
    m_window = new RenderWindow(
      sf::VideoMode({ 1920, 1080 }),
      "Rusted Kingdom"
    );

    if (!m_window->isOpen())
    {
      delete m_window;

      throw RuntimeErrorException(
        "Failed to create RenderWindow."
      );
    }
  }

  void Application::registerServices()
  {
    m_serviceLocator.registerService(MakeShared<ScenesManager>());
  }
}