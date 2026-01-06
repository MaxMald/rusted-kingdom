#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkServiceLocator.h"
#include "rkIRuntimeDevTools.h"

using sf::RenderWindow;
using sf::Time;

namespace rk
{
  class ScenesManager;
  class WindowManager;
  class ViewsManager;
  class InputManager;

  class Application : public NonCopyable
  {
  public:
    Application();
    ~Application();

    void prepare();
    void run(const String& initialScene);
    void destroy();

  private:
    SharedPtr<IRuntimeDevTools> m_runtimeDevTools;
    ServiceLocator* m_serviceLocator;
    SharedPtr<ScenesManager> m_scenesManager;
    SharedPtr<WindowManager> m_windowManager;
    SharedPtr<ViewsManager> m_viewManager;
    SharedPtr<InputManager> m_inputManager;

    void registerServices();
    void registerScenes();
    void update(RenderWindow&, const Time&);
    void draw(RenderWindow&);
  };
}