#include "rkRigidBodyComponentFactory.h"
#include "rkServiceLocator.h"
#include "rkScenesManager.h"
#include "rkIScene.h"
#include "rkCircleCollider.h"
#include "rkRigidBodyComponent.h"
#include "rkRigidBodyDebuggedComponent.h"
#include "rkGameObject.h"
#include "rkPhysicWorld.h"

namespace rk
{
  namespace rigidBodyComponentFactory
  {
    UniquePtr<RigidBodyComponent> create(
      GameObject& gameObject,
      rigidBodyType::Type type,
      bool debug
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

      if (debug)
      {
        return MakeUnique<RigidBodyDebuggedComponent>(
          gameObject,
          physicWorld,
          type
        );
      }

      return MakeUnique<RigidBodyComponent>(
        gameObject,
        physicWorld,
        type
      );
    }
  }
}