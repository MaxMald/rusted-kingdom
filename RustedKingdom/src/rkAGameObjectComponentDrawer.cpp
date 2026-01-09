#include "rkAGameObjectComponentDrawer.h"
#include "imgui.h"

namespace rk
{
  AGameObjectComponentDrawer::AGameObjectComponentDrawer(String componentName) :
    m_componentName(componentName)
  {
  }

  void AGameObjectComponentDrawer::draw(
    Component& component,
    sf::RenderWindow& window
  )
  {
    ImGui::PushID(&component);
    if (ImGui::CollapsingHeader(m_componentName.c_str()))
      onDraw(component, window);
    ImGui::PopID();
  }
}