#pragma once

#include "rkARuntimeDevToolComponent.h"

namespace rk
{
  class InputManager;
  class MouseInputManager;

  class MouseInfoRuntimeDevToolComponent : public ARuntimeDevToolComponent
  {
  public:
    MouseInfoRuntimeDevToolComponent(SharedPtr<InputManager>);
    ~MouseInfoRuntimeDevToolComponent() override = default;

  protected:
    SharedPtr<InputManager> m_inputManager;

    void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) override;
    void onDraw(sf::RenderWindow& window) override;

    void drawMouseInputManagerInfo(const MouseInputManager& mouseInputManager);
  };
}