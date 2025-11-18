#include "rkColliderComponentFactory.h"
#include "rkPhysicWorld.h"
#include "rkCircleCollider.h"
#include "rkCircleColliderComponent.h"

namespace rk
{
  ColliderComponentFactory::ColliderComponentFactory(PhysicWorld& physicWorld)
    : m_physicWorld(physicWorld)
  {
  }

  ColliderComponentFactory::~ColliderComponentFactory()
  {
  }

  UniquePtr<CircleColliderComponent> ColliderComponentFactory::createCircle(
    GameObject& gameObject,
    const Vector2f& center,
    float radius
  )
  {
    Collider* collider = m_physicWorld.createCollider(
      gameObject,
      colliderType::Circle
    );

    CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
    circleCollider->setCenter(center);
    circleCollider->setRadius(radius);

    return MakeUnique<CircleColliderComponent>(
      gameObject,
      m_physicWorld,
      circleCollider
    );
  }
}