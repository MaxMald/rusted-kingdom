#include "rkMouseInfoRuntimeDevToolComponent.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkInputManager.h"
#include "rkMouseInputManager.h"

namespace rk
{
  MouseInfoRuntimeDevToolComponent::MouseInfoRuntimeDevToolComponent(
    SharedPtr<InputManager> inputManager
  ) : ARuntimeDevToolComponent("Mouse Information"),
    m_inputManager(inputManager)
  {
  }
  void MouseInfoRuntimeDevToolComponent::onUpdate(
    sf::RenderWindow&,
    const sf::Time&
  )
  {
    // Implementation for updating mouse info can be added here.
  }

  void MouseInfoRuntimeDevToolComponent::onDraw(
    sf::RenderWindow&
  )
  {
    if (!m_inputManager)
      return;

    drawMouseInputManagerInfo(m_inputManager->getMouseInputManager());
  }

  void MouseInfoRuntimeDevToolComponent::drawMouseInputManagerInfo(const MouseInputManager& mouseInputManager)
  {
    Vector2i mousePosDesktop = mouseInputManager.getMousePosition();
    ImGui::Text("Mouse Position (Desktop): %d, %d", mousePosDesktop.x, mousePosDesktop.y);

    Vector2i mousePosWindow = mouseInputManager.getMousePositionRelativeToWindow();
    ImGui::Text("Mouse Position (Window Relative): %d, %d", mousePosWindow.x, mousePosWindow.y);

    Vector2f mousePosWorld = mouseInputManager.getMousePositionWorldCoordinates();
    ImGui::Text("Mouse Position (World Coords): %.2f, %.2f", mousePosWorld.x, mousePosWorld.y);
  }
}