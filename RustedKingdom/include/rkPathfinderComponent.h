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
    PathfinderComponent(
      GameObject&,
      SharedPtr<Pathfinder>
    );
    virtual ~PathfinderComponent();

    Vector<Vector2f> findPath(
      const Vector2f& start,
      const Vector2f& end
    );

  private:
    SharedPtr<Pathfinder> m_pathfinder;
    bool m_drawPoints;
  };
}