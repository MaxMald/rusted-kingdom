#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "rkAGameObjectComponentDrawer.h"
#include "rkNonCopyable.h"

namespace rk
{
  class Component;

  class GameObjectComponentDrawerService : public NonCopyable
  {
  public:
    GameObjectComponentDrawerService();
    ~GameObjectComponentDrawerService();

    void draw(
      sf::RenderWindow& window,
      Component& component
    );

  private:
    UnorderedMap<TypeIndex, UniquePtr<AGameObjectComponentDrawer>> m_componentDrawers;
    UniquePtr<AGameObjectComponentDrawer> m_defaultComponentDrawer;
  };
}