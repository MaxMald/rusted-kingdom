#pragma once

#include "rkNonCopyable.h"
#include "rkIColliderDrawer.h"
#include "rkCollider.h"

namespace rk
{
  class Collider;

  class ColliderDrawerService : public NonCopyable
  {
  public:
    ColliderDrawerService();
    ~ColliderDrawerService();

    void draw(
      sf::RenderWindow& window,
      const Collider& collider,
      const sf::Color& color
    );

  private:
    UnorderedMap<colliderType::Type, UniquePtr<IColliderDrawer>> m_colliderDrawers;
  };
}