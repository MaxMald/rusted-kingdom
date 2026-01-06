#pragma once

#include "rkIRuntimeDevTools.h"

namespace rk
{
  class NullRuntimeDevTools : public IRuntimeDevTools
  {
  public:
    void prepare(sf::RenderWindow&, ServiceLocator&) override {}
    void processEvent(const sf::Window&, const sf::Event&) override {}
    void update(sf::RenderWindow&, const sf::Time&) override {}
    void draw(sf::RenderWindow&) override {}
    void destroy() override {}
  };
}