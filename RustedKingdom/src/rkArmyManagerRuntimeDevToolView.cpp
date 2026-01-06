#include "rkArmyManagerRuntimeDevToolView.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkArmyManager.h"
#include "rkArmy.h"
#include "rkFaction.h"
#include "rkFactionManager.h"
#include "rkGameObject.h"

#include "scripts/rkUnitController.h"

namespace rk
{
  ArmyManagerRuntimeDevToolView::ArmyManagerRuntimeDevToolView(
    SharedPtr<ArmyManager> armyManager,
    SharedPtr<FactionManager> factionManager
  ) :
    ARuntimeDevToolView("Army Manager"),
    m_armyManager(armyManager),
    m_factionManager(factionManager)
  {
  }

  ArmyManagerRuntimeDevToolView::~ArmyManagerRuntimeDevToolView()
  {
  }

  void ArmyManagerRuntimeDevToolView::onUpdate(
    sf::RenderWindow&,
    const sf::Time&
  )
  {
    // No implementation needed
  }

  void ArmyManagerRuntimeDevToolView::onDraw(
    sf::RenderWindow&
  )
  {
    if (!m_armyManager || !m_factionManager)
      return;

    UnorderedMap<UInt32, SharedPtr<Army>> armies =
      m_armyManager->getAllArmies();

    String treeLabel = String::Format("Armies (%zu)", armies.size());
    if (ImGui::TreeNode(treeLabel.c_str()))
    {
      for (const auto& pair : armies)
        drawArmyElement(*(pair.second));

      ImGui::TreePop();
    }
  }

  void ArmyManagerRuntimeDevToolView::drawArmyElement(const Army& army)
  {
    if (ImGui::TreeNode(army.getName().c_str()))
    {
      ImGui::Text("ID: %u", army.getId());

      String factionName = getArmyFactionName(army);
      ImGui::Text("Faction: %s", factionName.c_str());

      String controlTypeStr = armyControlType::toString(army.getControlType());
      ImGui::Text("Control: %s", controlTypeStr.c_str());

      const Vector<UnitController*>& units = army.getUnits();
      drawUnitsTree(units);

      ImGui::TreePop();
    }
  }

  String ArmyManagerRuntimeDevToolView::getArmyFactionName(const Army& army)
  {
    Faction faction = m_factionManager->getFaction(army.getFactionType());
    return faction.getName();
  }

  void ArmyManagerRuntimeDevToolView::drawUnitsTree(
    const Vector<UnitController*>& units
  )
  {
    String label = String::Format("Units (%zu)", units.size());
    if (ImGui::TreeNode(label.c_str()))
    {
      for (const UnitController* unitController : units)
        drawUnitElement(*unitController);

      ImGui::TreePop();
    }
  }

  void ArmyManagerRuntimeDevToolView::drawUnitElement(
    const UnitController& unitController
  )
  {
    const GameObject& gameObject = unitController.getGameObject();

    String gameObjectName = gameObject.getName();
    if (gameObjectName.empty())
      gameObjectName = "<unnamed>";

    gameObjectName = String::Format("%s (%p)", gameObjectName.c_str(), &gameObject);
    
    if (ImGui::TreeNode(gameObjectName.c_str()))
    {
      const UnitDescription& unitDescription =
        unitController.getUnitDescription();

      ImGui::Text("Unit Descriptor Information:");
      ImGui::Text("Unit Name: %s", unitDescription.getName().c_str());
      ImGui::Text("Display Name: %s", unitDescription.getDisplayName().c_str());
      ImGui::Text("Health: %u", unitDescription.getHealth());
      ImGui::Text("Armor: %u", unitDescription.getArmor());
      ImGui::Text("Velocity: %.2f", unitDescription.getVelocity());

      ImGui::Separator();
      ImGui::Text("Unit Controller Information:");
      ImGui::Text("Current Health: %u", unitController.getCurrentHealth());

      ImGui::TreePop();
    }

  }
}