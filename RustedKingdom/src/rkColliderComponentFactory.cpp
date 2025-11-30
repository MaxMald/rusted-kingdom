#include "rkColliderComponentFactory.h"
#include "rkPhysicWorld.h"
#include "rkCircleCollider.h"
#include "rkColliderComponent.h"

namespace rk
{
  ColliderComponentFactory::ColliderComponentFactory(PhysicWorld& physicWorld)
    : m_physicWorld(physicWorld)
  {
  }

  ColliderComponentFactory::~ColliderComponentFactory()
  {
  }

  UniquePtr<ColliderComponent> ColliderComponentFactory::createCircle(
    GameObject& gameObject,
    const Vector2f& center,
    float radius,
    const String& colliderGroupKey
  )
  {
    Collider* collider = m_physicWorld.createCollider(
      gameObject,
      colliderType::Circle,
      colliderGroupKey
    );

    CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
    circleCollider->setCenter(center);
    circleCollider->setRadius(radius);

    return MakeUnique<ColliderComponent>(
      gameObject,
      m_physicWorld,
      circleCollider
    );
  }
}