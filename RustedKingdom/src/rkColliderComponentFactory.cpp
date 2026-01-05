#include "rkColliderComponentFactory.h"

#include "rkServiceLocator.h"
#include "rkScenesManager.h"
#include "rkIScene.h"
#include "rkGameObject.h"
#include "rkPhysicWorld.h"
#include "rkCircleCollider.h"
#include "rkColliderComponent.h"

namespace rk
{
  namespace colliderComponentFactory
  {
    UniquePtr<ColliderComponent> createCircle(
      GameObject& gameObject,
      const Vector2f& center,
      float radius,
      const String& colliderGroupKey
    )
    {
      SharedPtr<ScenesManager> scenesManager =
        ServiceLocator::Instance().getService<ScenesManager>();

      SharedPtr<IScene> activeScene = scenesManager->getActiveScene();
      if (!activeScene)
      {
        throw RuntimeErrorException(
          "No active scene found in ScenesManager."
        );
      }

      PhysicWorld& physicWorld = activeScene->getPhysicWorld();

      Collider* collider = physicWorld.createCollider(
        gameObject,
        colliderType::Circle,
        colliderGroupKey
      );

      CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
      circleCollider->setCenter(center);
      circleCollider->setRadius(radius);

      return MakeUnique<ColliderComponent>(
        gameObject,
        physicWorld,
        circleCollider
      );
    }
  }
}