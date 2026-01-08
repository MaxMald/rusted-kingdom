#pragma once

#include "rkIColliderDrawer.h"

namespace rk
{
  class NullColliderDrawer : public IColliderDrawer
  {
  public:
    NullColliderDrawer();
    ~NullColliderDrawer() override;

    void draw(
      sf::RenderWindow&,
      const Collider&,
      const sf::Color&
    ) override;
  };
}
