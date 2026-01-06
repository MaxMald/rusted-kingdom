#include "rkFactionManagerRuntimeDevToolView.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkFactionManager.h"
#include "rkFaction.h"

namespace rk
{
  FactionManagerRuntimeDevToolView::FactionManagerRuntimeDevToolView(
    SharedPtr<FactionManager> factionManager
  ) : ARuntimeDevToolView("Faction Manager"),
    m_factionManager(factionManager)
  {
  }

  FactionManagerRuntimeDevToolView::~FactionManagerRuntimeDevToolView()
  {
  }

  void FactionManagerRuntimeDevToolView::onUpdate(
    sf::RenderWindow&,
    const sf::Time&
  )
  {
    // No implementation needed
  }

  void FactionManagerRuntimeDevToolView::onDraw(
    sf::RenderWindow& window
  )
  {
    if (!m_factionManager)
      return;

    Vector<Faction> factions = m_factionManager->getAllFactions();
    String treeLabel = String::Format("Factions (%zu)", factions.size());

    if (ImGui::TreeNode(treeLabel.c_str()))
    {
      for (const auto& faction : factions)
        drawFactionElement(faction);

      ImGui::TreePop();
    }
  }

  void FactionManagerRuntimeDevToolView::drawFactionElement(const Faction& faction)
  {
    if (ImGui::TreeNode(faction.getName().c_str()))
    {
      ImGui::Text("Type: %d", static_cast<int>(faction.getType()));

      String pathStr = faction.getFactionAssetsPath().string();
      ImGui::Text("Assets Path: %s", pathStr.c_str());

      ImGui::TreePop();
    }
  }
}