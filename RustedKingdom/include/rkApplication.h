#pragma once

#include <SFML/Graphics.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkServiceLocator.h"

using sf::RenderWindow;

namespace rk
{
  class ScenesManager;

  class Application : public NonCopyable
  {
  public:
    Application();
    ~Application();

    void prepare();
    void run();
    void destroy();

  private:
    RenderWindow* m_window;
    ServiceLocator m_serviceLocator;
    SharedPtr<ScenesManager> m_scenesManager;

    void update(float deltaTime);
    void draw();

    void createWindow();
    void registerServices();
  };
}