#pragma once

#include "rkAGameObjectComponentDrawer.h"

namespace rk
{
  class ColliderGameObjectComponentDrawer : public AGameObjectComponentDrawer
  {
  public:
    ColliderGameObjectComponentDrawer();
    ~ColliderGameObjectComponentDrawer();

  protected:
    void onDraw(Component& component, sf::RenderWindow& window) override;
  };
}