#include "rkCollidersDrawerRuntimeDevToolComponent.h"
#include "rkPhysicWorld.h"
#include "rkCollidersGroup.h"
#include "rkScenesManager.h"
#include "rkIScene.h"

namespace rk
{
  CollidersDrawerRuntimeDevToolComponent::CollidersDrawerRuntimeDevToolComponent(
    SharedPtr<ScenesManager> scenesManager
  ) : ARuntimeDevToolComponent("Collider Drawer Tool"),
    m_colliderGroupDrawers(),
    m_scenesManager(scenesManager),
    m_drawerService()
  {
  }

  CollidersDrawerRuntimeDevToolComponent::~CollidersDrawerRuntimeDevToolComponent()
  {
  }

  void CollidersDrawerRuntimeDevToolComponent::onUpdate(
    sf::RenderWindow&,
    const sf::Time&
  )
  {
    // Nothing to do
  }

  void CollidersDrawerRuntimeDevToolComponent::onDraw(sf::RenderWindow& window)
  {
    SharedPtr<IScene> activeScene = m_scenesManager->getActiveScene();
    if (!activeScene)
      return;

    PhysicWorld& physicWorld = activeScene->getPhysicWorld();

    updateColliderGroupDrawers(physicWorld);

    for (const auto groupDrawer : m_colliderGroupDrawers)
      groupDrawer->draw(window, physicWorld);
  }

  void CollidersDrawerRuntimeDevToolComponent::updateColliderGroupDrawers(
    const PhysicWorld& physicWorld
  )
  {
    // Remove obsolete group drawers
    Int32 numCurrentGroupDrawers = static_cast<Int32>(m_colliderGroupDrawers.size());
    for (Int32 i = numCurrentGroupDrawers - 1; i >= 0; --i)
    {
      const SharedPtr<ColliderGroupDrawer>& groupDrawer = m_colliderGroupDrawers[i];
      if (!physicWorld.hasColliderGroup(groupDrawer->getColliderGroupKey()))
        m_colliderGroupDrawers.erase(m_colliderGroupDrawers.begin() + i);
    }

    // Add new group drawers
    Vector<String> colliderGroupKeys = physicWorld.getCollidersGroupKeys();
    for (const String& groupKey : colliderGroupKeys)
    {
      auto it = std::find_if(
        m_colliderGroupDrawers.begin(),
        m_colliderGroupDrawers.end(),
        [&groupKey](const SharedPtr<ColliderGroupDrawer>& drawer)
        {
          return drawer->getColliderGroupKey() == groupKey;
        }
      );

      if (it == m_colliderGroupDrawers.end())
      {
        m_colliderGroupDrawers.push_back(
          MakeShared<ColliderGroupDrawer>(groupKey, m_drawerService)
        );
      }
    }
  }
}


