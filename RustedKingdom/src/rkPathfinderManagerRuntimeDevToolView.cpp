#include "rkPathfinderManagerRuntimeDevToolView.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkPathfinderManager.h"
#include "rkPathfinder.h"

namespace rk
{
  PathfinderManagerRuntimeDevToolView::PathfinderManagerRuntimeDevToolView(
    SharedPtr<PathfinderManager> pathfinderManager
  ) : ARuntimeDevToolView("Pathfinder Manager"),
    m_pathfinderManager(pathfinderManager)
  {
  }

  PathfinderManagerRuntimeDevToolView::~PathfinderManagerRuntimeDevToolView()
  {
  }

  void PathfinderManagerRuntimeDevToolView::onUpdate(
    sf::RenderWindow&,
    const sf::Time&
  )
  {
    // No update logic needed for now
  }

  void PathfinderManagerRuntimeDevToolView::onDraw(sf::RenderWindow&)
  {
    if (!m_pathfinderManager)
      return;
    
    UnorderedMap<String, SharedPtr<Pathfinder>> pathfinders =
      m_pathfinderManager->getAllPathfinders();

    String pathfinderLabel = String::Format("Pathfinders (%u)", pathfinders.size());
    if (ImGui::TreeNode(pathfinderLabel.c_str()))
    {
      for (const auto& pair : pathfinders)
      {
        drawPathfinderElement(pair.first, *(pair.second));
      }

      ImGui::TreePop();
    }
  }

  void PathfinderManagerRuntimeDevToolView::drawPathfinderElement(
    const String& key,
    const Pathfinder& pathfinder
  )
  {
    if (ImGui::TreeNode(key.c_str()))
    {
      ImGui::Text("Dimensions: (%u x %u)", pathfinder.getWidth(), pathfinder.getHeight());
      ImGui::Text("Total of %u nodes", pathfinder.getWidth() * pathfinder.getHeight());
      ImGui::TreePop();
    }
  }
}