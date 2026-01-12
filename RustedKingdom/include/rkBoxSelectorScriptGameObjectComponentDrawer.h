#pragma once

#include "rkAGameObjectComponentDrawer.h"

namespace rk
{
  class BoxSelectorScriptGameObjectComponentDrawer : public AGameObjectComponentDrawer
  {
  public:
    BoxSelectorScriptGameObjectComponentDrawer();
    ~BoxSelectorScriptGameObjectComponentDrawer();

  protected:
    void onDraw(
      Component& component,
      sf::RenderWindow& window
    );
  };
}