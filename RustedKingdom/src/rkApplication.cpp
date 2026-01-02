#include "rkApplication.h"

#include <iostream>

#include "rkScenesManager.h"
#include "rkWindowManager.h"
#include "rkAssetManager.h"
#include "rkViewsManager.h"
#include "rkInputManager.h"
#include "rkFactionManager.h"
#include "rkArmyManager.h"
#include "rkUnitDescriptionManager.h"
#include "rkPathfinderManager.h"
#include "rkMainScene.h"

using std::optional;
using sf::Time;
using sf::RenderStates;
using sf::Clock;

namespace rk
{
  Application::Application() :
    m_scenesManager(nullptr),
    m_windowManager(nullptr),
    m_viewManager(nullptr),
    m_serviceLocator(nullptr)
  {
  }

  Application::~Application()
  {
  }

  void Application::prepare()
  {
    ServiceLocator::Prepare();
    m_serviceLocator = &ServiceLocator::Instance();

    registerServices();

    m_scenesManager =
      m_serviceLocator->getService<ScenesManager>();
    m_windowManager =
      m_serviceLocator->getService<WindowManager>();
    m_viewManager =
      m_serviceLocator->getService<ViewsManager>();
    m_inputManager =
      m_serviceLocator->getService<InputManager>();

    m_windowManager->createWindow();
    m_serviceLocator->initializeServices();

    registerScenes();
    m_scenesManager->initScenes(*m_serviceLocator);
  }

  void Application::run(const String& initialScene)
  {
    m_scenesManager->setNextScene(initialScene);
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
    ServiceLocator::Shutdown();
  }

  void Application::update(float deltaTime)
  {
    m_inputManager->update();
    m_viewManager->updateRenderWindowView();
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
    m_serviceLocator->registerService(MakeShared<AssetManager>());
    m_serviceLocator->registerService(MakeShared<ScenesManager>());
    m_serviceLocator->registerService(MakeShared<WindowManager>());
    m_serviceLocator->registerService(MakeShared<ViewsManager>());
    m_serviceLocator->registerService(MakeShared<InputManager>());
    m_serviceLocator->registerService(MakeShared<FactionManager>());
    m_serviceLocator->registerService(MakeShared<ArmyManager>());
    m_serviceLocator->registerService(MakeShared<UnitDescriptionManager>());
    m_serviceLocator->registerService(MakeShared<PathfinderManager>());
  }

  void Application::registerScenes()
  {
    m_scenesManager->registerScene("MainScene", MakeShared<MainScene>());
  }
}