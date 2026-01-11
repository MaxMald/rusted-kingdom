#pragma once

#include "rkAGameObjectComponentDrawer.h"

namespace rk
{
  class AgentPathMovementGameObjectComponentDrawer : public AGameObjectComponentDrawer
  {
  public:
    AgentPathMovementGameObjectComponentDrawer();
    ~AgentPathMovementGameObjectComponentDrawer();

  protected:
    void onDraw(Component& component, sf::RenderWindow& window) override;
  };
}
