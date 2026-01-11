#include "rkAgentPathMovementGameObjectComponentDrawer.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include "scripts/rkAgentPathMovement.h"

namespace rk
{
  AgentPathMovementGameObjectComponentDrawer::
    AgentPathMovementGameObjectComponentDrawer()
    : AGameObjectComponentDrawer("Agent Path Movement")
  {
  }

  AgentPathMovementGameObjectComponentDrawer::
    ~AgentPathMovementGameObjectComponentDrawer()
  {
  }

  void AgentPathMovementGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow&
  )
  {
    AgentPathMovement& agentPathMovement =
      static_cast<AgentPathMovement&>(component);

    ImGui::Text("Is Moving: %s", agentPathMovement.isMoving() ? "Yes" : "No");
    ImGui::Text("Speed: %.2f", agentPathMovement.getSpeed());
  }
}