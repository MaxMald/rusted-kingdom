#pragma once

#include "rkPrerequisites.h"

namespace sf
{
  class Window;
  class RenderWindow;
  class Time;
  class Event;
}

namespace rk
{
  class ServiceLocator;

  class IRuntimeDevTools
  {
  public:
    virtual ~IRuntimeDevTools() = default;

    virtual void prepare(sf::RenderWindow& window, ServiceLocator&) = 0;
    virtual void processEvent(const sf::Window& window, const sf::Event& event) = 0;
    virtual void update(sf::RenderWindow& window, const sf::Time& elapsed) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void destroy() = 0;
  };
}