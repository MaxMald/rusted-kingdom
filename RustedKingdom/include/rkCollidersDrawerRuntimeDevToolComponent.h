#pragma once

#include "rkARuntimeDevToolComponent.h"
#include "rkColliderGroupDrawer.h"
#include "rkColliderDrawerService.h"

namespace rk
{
  class PhysicWorld;
  class ScenesManager;

  class CollidersDrawerRuntimeDevToolComponent : public ARuntimeDevToolComponent
  {
  public:
    CollidersDrawerRuntimeDevToolComponent(SharedPtr<ScenesManager> scenesManager);
    ~CollidersDrawerRuntimeDevToolComponent() override;

  protected:
    void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) override;
    void onDraw(sf::RenderWindow& window) override;

  private:
    Vector<SharedPtr<ColliderGroupDrawer>> m_colliderGroupDrawers;
    SharedPtr<ScenesManager> m_scenesManager;
    ColliderDrawerService m_drawerService;

    void updateColliderGroupDrawers(const PhysicWorld& physicWorld);
  };
}