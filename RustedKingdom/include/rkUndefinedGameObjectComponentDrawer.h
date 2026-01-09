#pragma once

#include "rkAGameObjectComponentDrawer.h"

namespace rk
{
  class UndefinedGameObjectComponentDrawer : public AGameObjectComponentDrawer
  {
  public:
    UndefinedGameObjectComponentDrawer();
    virtual ~UndefinedGameObjectComponentDrawer();

  protected:
    virtual void onDraw(Component& component, sf::RenderWindow& window) override;
  };
}