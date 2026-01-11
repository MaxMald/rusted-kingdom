#include "rkColliderGameObjectComponentDrawer.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkColliderComponent.h"
#include "rkCollider.h"

namespace rk
{
  ColliderGameObjectComponentDrawer::
    ColliderGameObjectComponentDrawer()
    : AGameObjectComponentDrawer("Collider")
  {
  }

  ColliderGameObjectComponentDrawer::
    ~ColliderGameObjectComponentDrawer()
  {
  }

  void ColliderGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow&
  )
  {
    ColliderComponent& colliderComponent =
      static_cast<ColliderComponent&>(component);

    String colliderType = colliderType::toString(
      colliderComponent.getColliderType()
    );

    ImGui::Text("Type: %s", colliderType.c_str());
    ImGui::Text(
      "Center: (%.2f, %.2f)",
      colliderComponent.getCenter().x,
      colliderComponent.getCenter().y
    );
  }
}