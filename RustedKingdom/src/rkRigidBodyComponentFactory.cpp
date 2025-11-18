#include "rkRigidBodyComponentFactory.h"
#include "rkCircleCollider.h"
#include "rkRigidBodyComponent.h"
#include "rkRigidBodyDebuggedComponent.h"
#include "rkGameObject.h"
#include "rkPhysicWorld.h"

namespace rk
{
  RigidBodyComponentFactory::RigidBodyComponentFactory(
    PhysicWorld& physicWorld
  ) :
    m_physicWorld(physicWorld)
  {
  }

  RigidBodyComponentFactory::~RigidBodyComponentFactory()
  {
  }

  UniquePtr<RigidBodyComponent>
  RigidBodyComponentFactory::create(
    GameObject& gameObject,
    rigidBodyType::Type type,
    bool debug
  )
  {
    if (debug)
    {
      return MakeUnique<RigidBodyDebuggedComponent>(
        gameObject,
        m_physicWorld,
        type
      );
    }

    return MakeUnique<RigidBodyComponent>(
      gameObject,
      m_physicWorld,
      type
    );
  }
}