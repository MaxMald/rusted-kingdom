#pragma once

#include "rkARuntimeDevToolView.h"

namespace rk
{
  class ScenesManager;
  class PhysicWorld;
  class CircleCollider;
  class Collider;

  class PhysicWorldRuntimeDevToolView : public rk::ARuntimeDevToolView
  {
  public:
    PhysicWorldRuntimeDevToolView(SharedPtr<ScenesManager>);
    ~PhysicWorldRuntimeDevToolView() override;

  protected:
    SharedPtr<ScenesManager> m_scenesManager;

    void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) override;
    void onDraw(sf::RenderWindow& window) override;

    void drawPhysicWorldInfo(const PhysicWorld&);
    void drawColliderGroupsInfo(const Vector<String>&, const PhysicWorld&);
    void drawColliderGroupInfo(const String&, const Vector<UniquePtr<Collider>>&);
    void drawColliderInfo(const Collider&);
    void drawColliderTypeInfo(const Collider&);
    void drawCircleColliderInfo(const CircleCollider&);
  };
}