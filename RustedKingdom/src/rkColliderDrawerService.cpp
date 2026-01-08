#include "rkColliderDrawerService.h"

#include "rkNullColliderDrawer.h"
#include "rkCircleColliderDrawer.h"

namespace rk
{
  ColliderDrawerService::ColliderDrawerService() :
    m_colliderDrawers()
  {
    m_colliderDrawers[colliderType::Undefined] = MakeUnique<NullColliderDrawer>();
    m_colliderDrawers[colliderType::Circle] = MakeUnique<CircleColliderDrawer>();
  }

  ColliderDrawerService::~ColliderDrawerService()
  {
  }

  void ColliderDrawerService::draw(
    sf::RenderWindow& window,
    const Collider& collider,
    const sf::Color& color
  )
  {
    auto it = m_colliderDrawers.find(collider.getType());
    if (it != m_colliderDrawers.end())
    {
      IColliderDrawer* drawer = it->second.get();
      if (drawer)
        drawer->draw(window, collider, color);
    }

    // TODO log unknown collider type
  }
}