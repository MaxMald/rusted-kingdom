#include "rkBoxSelectorScriptGameObjectComponentDrawer.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include "scripts/rkBoxSelectorScript.h"

namespace rk
{
  BoxSelectorScriptGameObjectComponentDrawer::
    BoxSelectorScriptGameObjectComponentDrawer() :
    AGameObjectComponentDrawer("Box Selector Script")
  {
  }

  BoxSelectorScriptGameObjectComponentDrawer::
    ~BoxSelectorScriptGameObjectComponentDrawer()
  {
  }

  void BoxSelectorScriptGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow&
  )
  {
    BoxSelectorScript& boxSelectorScript =
      static_cast<BoxSelectorScript&>(component);
    
    ImGui::Text("Is Selecting: %s",
      boxSelectorScript.isSelecting() ? "Yes" : "No"
    );

    if (boxSelectorScript.isSelecting())
    {
      Vector2f boxP1 = boxSelectorScript.getBoxP1();
      Vector2f boxP2 = boxSelectorScript.getBoxP2();
      ImGui::Text("Box P1: (%.2f, %.2f)", boxP1.x, boxP1.y);
      ImGui::Text("Box P2: (%.2f, %.2f)", boxP2.x, boxP2.y);
    }
  }
}