#include "rkUndefinedGameObjectComponentDrawer.h"

#include <typeinfo>

#include "imgui.h"
#include "rkComponent.h"

namespace rk
{
  UndefinedGameObjectComponentDrawer::UndefinedGameObjectComponentDrawer() :
    AGameObjectComponentDrawer("Unsupported Component")
  {
  }

  UndefinedGameObjectComponentDrawer::~UndefinedGameObjectComponentDrawer()
  {
  }

  void UndefinedGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow&
  )
  {
    ImGui::Text("No drawer available for this component.");
    ImGui::Text("Component type: %s", typeid(component).name());
  }
}