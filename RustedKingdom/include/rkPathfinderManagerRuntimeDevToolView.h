#pragma once

#include "rkARuntimeDevToolView.h"

namespace rk
{
  class Pathfinder;
  class PathfinderManager;

  class PathfinderManagerRuntimeDevToolView : public ARuntimeDevToolView
  {
  public:
    PathfinderManagerRuntimeDevToolView(
      SharedPtr<PathfinderManager> pathfinderManager
    );
    virtual ~PathfinderManagerRuntimeDevToolView();

  protected:
    virtual void onUpdate(sf::RenderWindow&, const sf::Time&) override;
    virtual void onDraw(sf::RenderWindow&) override;

  private:
    SharedPtr<PathfinderManager> m_pathfinderManager;

    void drawPathfinderElement(
      const String& key,
      const Pathfinder& pathfinder
    );
  };
}