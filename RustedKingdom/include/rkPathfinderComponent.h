#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkComponent.h"

using sf::Vector2f;

namespace rk
{
  class Pathfinder;

  class PathfinderComponent : public Component
  {
  public:
    PathfinderComponent(GameObject&);
    virtual ~PathfinderComponent();

    void setPathfinder(SharedPtr<Pathfinder> pathfinder);

    Vector<Vector2f> findPath(
      const Vector2f& start,
      const Vector2f& end
    );

  private:
    SharedPtr<Pathfinder> m_pathfinder;
    bool m_drawPoints;
  };
}