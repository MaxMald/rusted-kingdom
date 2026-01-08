#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkPrerequisites.h"

namespace rk
{
  class Collider;

  class IColliderDrawer
  {
  public:
    virtual ~IColliderDrawer() = default;

    virtual void draw(
      sf::RenderWindow& window,
      const Collider& collider,
      const sf::Color& color
    ) = 0;

  protected:
    IColliderDrawer() = default;
  };
}