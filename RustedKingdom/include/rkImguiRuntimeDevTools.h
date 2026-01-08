#pragma once

#include "rkIRuntimeDevTools.h"
#include "rkServiceLocator.h"
#include "rkARuntimeDevToolView.h"
#include "rkMouseInfoRuntimeDevToolComponent.h"

namespace rk
{
  class ImguiRuntimeDevTools : public IRuntimeDevTools
  {
  public:
    void prepare(sf::RenderWindow& window, ServiceLocator&) override;
    void processEvent(const sf::Window& window, const sf::Event& event) override;
    void update(sf::RenderWindow& window, const sf::Time& elapsed) override;
    void draw(sf::RenderWindow& window) override;
    void destroy() override;

  private:
    SharedPtr<MouseInfoRuntimeDevToolComponent> m_mouseInfoComponent;
    Vector<SharedPtr<ARuntimeDevToolView>> m_views;
  };
}
