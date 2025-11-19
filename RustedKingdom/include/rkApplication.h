#pragma once

#include <SFML/Graphics.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkServiceLocator.h"

using sf::RenderWindow;

namespace rk
{
  class ScenesManager;
  class WindowManager;

  class Application : public NonCopyable
  {
  public:
    Application();
    ~Application();

    void prepare();
    void run(const String& initialScene);
    void destroy();

  private:
    ServiceLocator m_serviceLocator;
    SharedPtr<ScenesManager> m_scenesManager;
    SharedPtr<WindowManager> m_windowManager;

    void registerServices();
    void registerScenes();
    void update(float deltaTime);
    void draw(RenderWindow&);
  };
}