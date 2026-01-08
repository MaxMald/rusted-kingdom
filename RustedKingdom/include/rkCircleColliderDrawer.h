#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "rkIColliderDrawer.h"

namespace sf
{
  class CircleCollider;
}

namespace rk
{
  class CircleColliderDrawer : public IColliderDrawer
  {
  public:
    CircleColliderDrawer();
    ~CircleColliderDrawer() override;

    void draw(
      sf::RenderWindow&,
      const Collider&,
      const sf::Color&
    ) override;

  protected:
    sf::CircleShape m_sfmlCircleShape;
  };
}