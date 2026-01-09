#include "rkGameObjectComponentDrawerService.h"
#include "rkUndefinedGameObjectComponentDrawer.h"
#include "rkComponent.h"

namespace rk
{
  GameObjectComponentDrawerService::GameObjectComponentDrawerService()
  {
    m_defaultComponentDrawer = MakeUnique<UndefinedGameObjectComponentDrawer>();

    // Add other component drawers here
  }

  GameObjectComponentDrawerService::~GameObjectComponentDrawerService() = default;

  void GameObjectComponentDrawerService::draw(
    sf::RenderWindow& window,
    Component& component
  )
  {
    TypeIndex componentType = TypeIndex(typeid(component));
    auto it = m_componentDrawers.find(componentType);
    if (it != m_componentDrawers.end())
    {
      it->second->draw(component, window);
    }
    else
    {
      m_defaultComponentDrawer->draw(component, window);
    }
  }
}