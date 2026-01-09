#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "rkPrerequisites.h"

namespace rk
{
  class Component;

  class AGameObjectComponentDrawer
  {
  public:
    virtual ~AGameObjectComponentDrawer() = default;

    void draw(Component& component, sf::RenderWindow& window);

  protected:
    String m_componentName;
    
    AGameObjectComponentDrawer(String componentName);

    virtual void onDraw(Component& component, sf::RenderWindow& window) = 0;
  };
}