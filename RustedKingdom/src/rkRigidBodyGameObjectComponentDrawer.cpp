#include "rkRigidBodyGameObjectComponentDrawer.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkRigidBodyComponent.h"

namespace rk
{
  RigidBodyGameObjectComponentDrawer::
    RigidBodyGameObjectComponentDrawer()
    : AGameObjectComponentDrawer("Rigid Body")
  {
  }

  RigidBodyGameObjectComponentDrawer::
    ~RigidBodyGameObjectComponentDrawer()
  {
  }

  void RigidBodyGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow&
  )
  {
    RigidBodyComponent& rigidBodyComponent =
       static_cast<RigidBodyComponent&>(component);

    String rigidBodyType = rigidBodyType::toString(
      rigidBodyComponent.getType()
    );

    ImGui::Text("Type: %s", rigidBodyType.c_str());
    ImGui::Text("Mass: %.2f", rigidBodyComponent.getMass());
    ImGui::Text(
      "Velocity: (%.2f, %.2f)",
      rigidBodyComponent.getVelocity().x,
      rigidBodyComponent.getVelocity().y
    );
  }
}