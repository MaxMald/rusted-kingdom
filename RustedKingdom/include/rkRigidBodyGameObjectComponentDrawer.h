#pragma once

#include "rkAGameObjectComponentDrawer.h"

namespace rk
{
  class RigidBodyGameObjectComponentDrawer : public AGameObjectComponentDrawer
  {
  public:
    RigidBodyGameObjectComponentDrawer();
    ~RigidBodyGameObjectComponentDrawer();

  protected:
    void onDraw(Component& component, sf::RenderWindow& window) override;
  };
}