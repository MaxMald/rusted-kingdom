#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include "rkPrerequisites.h"

namespace rk
{
  class Pathfinder;

  class PathfinderView : public sf::Drawable
  {
  public:
    explicit PathfinderView(Pathfinder& pathfinder);
    ~PathfinderView() override = default;

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;

  private:
    Pathfinder& m_pathfinder;
  };
}