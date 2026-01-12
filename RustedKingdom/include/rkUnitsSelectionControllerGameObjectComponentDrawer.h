#pragma once

#include "rkAGameObjectComponentDrawer.h"

namespace rk
{
  class UnitsSelectionControllerGameObjectComponentDrawer : 
    public AGameObjectComponentDrawer
  {
  public:
    UnitsSelectionControllerGameObjectComponentDrawer();
    virtual ~UnitsSelectionControllerGameObjectComponentDrawer();

  protected:
    virtual void onDraw(Component& component, sf::RenderWindow& window) override;
  };
}