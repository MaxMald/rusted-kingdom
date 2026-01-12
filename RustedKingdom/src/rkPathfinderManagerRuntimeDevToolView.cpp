#include "rkPathfinderManagerRuntimeDevToolView.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkPathfinderManager.h"
#include "rkPathfinder.h"
#include "rkPathfinderRuntimeDevToolDrawer.h"

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

  void PathfinderManagerRuntimeDevToolView::onDraw(sf::RenderWindow& window)
  {
    if (!m_pathfinderManager)
      return;
    
    UnorderedMap<String, SharedPtr<Pathfinder>> pathfinders =
      m_pathfinderManager->getAllPathfinders();

    ImGui::Text("Total of Pathfinders : %u", pathfinders.size());

    updatePathfinderDrawers();
    drawPathfinderDrawers(window);
  }

  void PathfinderManagerRuntimeDevToolView::updatePathfinderDrawers()
  {
    if (!m_pathfinderManager)
      return;

    const auto& pathfinders = m_pathfinderManager->getAllPathfinders();

    // For each pathfinder in the manager, ensure a drawer exists
    for (const auto& pair : pathfinders)
    {
      const SharedPtr<Pathfinder>& pathfinder = pair.second;
      const String& name = pair.first;

      if (!hasPathfinderDrawer(name))
      {
        m_pathfinderDrawers.emplace_back(
          MakeShared<PathfinderRuntimeDevToolDrawer>(name, pathfinder)
        );
      }
    }

    // Remove any drawer that no longer has a corresponding pathfinder
    for (SizeT i = m_pathfinderDrawers.size(); i-- > 0;)
    {
      const String& drawerName = m_pathfinderDrawers[i]->getName();
      if (pathfinders.find(drawerName) == pathfinders.end())
      {
        m_pathfinderDrawers.erase(m_pathfinderDrawers.begin() + i);
      }
    }
  }

  void PathfinderManagerRuntimeDevToolView::drawPathfinderDrawers(
    sf::RenderWindow& window
  )
  {
    for (const auto& drawer : m_pathfinderDrawers)
      drawer->draw(window);
  }

  bool PathfinderManagerRuntimeDevToolView::hasPathfinderDrawer(
    const String& key
  ) const
  {
    for (const auto& drawer : m_pathfinderDrawers)
    {
      if (drawer->getName() == key)
        return true;
    }
    return false;
  }
}