#include "rkGameObjectComponentDrawerService.h"
#include "rkUndefinedGameObjectComponentDrawer.h"
#include "rkSpriteComponent.h"
#include "rkSpriteGameObjectComponentDrawer.h"
#include "rkComponent.h"
#include "rkAnimationStateMachineGameObjectComponentDrawer.h"
#include "rkAnimationStateMachineComponent.h"
#include "rkUnitControllerGameObjectComponentDrawer.h"
#include "rkAgentPathMovementGameObjectComponentDrawer.h"

#include "scripts/rkUnitController.h"
#include "scripts/rkAgentPathMovement.h"

namespace rk
{
  GameObjectComponentDrawerService::GameObjectComponentDrawerService()
  {
    m_defaultComponentDrawer = MakeUnique<UndefinedGameObjectComponentDrawer>();

    m_componentDrawers[TypeIndex(typeid(SpriteComponent))] = 
      MakeUnique<SpriteGameObjectComponentDrawer>();

    m_componentDrawers[TypeIndex(typeid(AnimationStateMachineComponent))] =
      MakeUnique<AnimationStateMachineGameObjectComponentDrawer>();

    m_componentDrawers[TypeIndex(typeid(UnitController))] =
      MakeUnique<UnitControllerGameObjectComponentDrawer>();

    m_componentDrawers[TypeIndex(typeid(AgentPathMovement))] =
      MakeUnique<AgentPathMovementGameObjectComponentDrawer>();
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