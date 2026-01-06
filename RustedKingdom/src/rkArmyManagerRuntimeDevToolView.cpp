#include "rkArmyManagerRuntimeDevToolView.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkArmyManager.h"
#include "rkArmy.h"
#include "rkFaction.h"
#include "rkFactionManager.h"

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
      ImGui::Text("Faction: %s", getArmyFactionName(army).c_str());

      String controlTypeStr = armyControlType::toString(army.getControlType());
      ImGui::Text("Control: %s", controlTypeStr);
      ImGui::Text("Number of Units: %zu", army.getUnits().size());

      ImGui::TreePop();
    }
  }

  const String& ArmyManagerRuntimeDevToolView::getArmyFactionName(const Army& army)
  {
    Faction faction = m_factionManager->getFaction(army.getFactionType());
    return faction.getName();
  }
}