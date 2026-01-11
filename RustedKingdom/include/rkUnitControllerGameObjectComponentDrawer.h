#pragma once

#include "rkAGameObjectComponentDrawer.h"

namespace rk
{
  class UnitControllerGameObjectComponentDrawer : public AGameObjectComponentDrawer
  {
  public:
    UnitControllerGameObjectComponentDrawer();
    ~UnitControllerGameObjectComponentDrawer() override;

  protected:
    void onDraw(
      Component& component,
      sf::RenderWindow& window
    ) override;
  };
}