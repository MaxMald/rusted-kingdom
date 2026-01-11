#include "rkUnitControllerGameObjectComponentDrawer.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkArmy.h"
#include "rkUnitDescription.h"

#include "scripts/rkUnitController.h"

namespace rk
{
  UnitControllerGameObjectComponentDrawer::UnitControllerGameObjectComponentDrawer()
    : AGameObjectComponentDrawer("Unit Controller")
  {
  }

  UnitControllerGameObjectComponentDrawer::
    ~UnitControllerGameObjectComponentDrawer()
  {
  }

  void UnitControllerGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow&
  )
  {
    UnitController& unitController =
      static_cast<UnitController&>(component);

    SharedPtr<Army> unitArmy = unitController.getArmy();
    if (!unitArmy)
    {
      ImGui::Text("Army: <none>");
    }
    else
    {
      String armyName = unitArmy->getName();
      ImGui::Text("Army: %s", armyName.c_str());
    }

    const UnitDescription& unitDescription = unitController.getUnitDescription();
    ImGui::Separator();
    ImGui::Text("Unit Description:");
    ImGui::Text("  Name: %s", unitDescription.getName().c_str());
    ImGui::Text("  Display Name: %s", unitDescription.getDisplayName().c_str());
    ImGui::Text("  Velocity: %.2f", unitDescription.getVelocity());
    ImGui::Text("  Health: %d", unitDescription.getHealth());
    ImGui::Text("  Armor: %d", unitDescription.getArmor());
    ImGui::Separator();
    ImGui::Text("Current Health: %d", unitController.getCurrentHealth());
  }
}