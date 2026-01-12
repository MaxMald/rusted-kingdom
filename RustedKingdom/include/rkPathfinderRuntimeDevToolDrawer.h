#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class Pathfinder;
  class PathfinderRuntimeDevToolDrawer : public NonCopyable
  {
  public:
    PathfinderRuntimeDevToolDrawer(const String& name, SharedPtr<Pathfinder> pathfinder);
    ~PathfinderRuntimeDevToolDrawer();

    const String& getName() const;

    void draw(sf::RenderWindow& window);

  private:
    String m_name;
    bool m_drawPathfindingGrid;
    SharedPtr<Pathfinder> m_pathfinder;

    void drawPathfinderGrid(sf::RenderWindow& window);
  };
}