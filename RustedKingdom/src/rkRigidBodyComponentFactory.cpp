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
  RigidBodyComponentFactory::createWithCircleCollider(
    GameObject& gameObject,
    rigidBodyType::Type type,
    const Vector2f& center,
    float radius,
    bool debug
  )
  {
    UniquePtr<Collider> collider = MakeUnique<CircleCollider>(
      center,
      radius
    );

    if (debug)
    {
      return MakeUnique<RigidBodyDebuggedComponent>(
        gameObject,
        m_physicWorld,
        type,
        std::move(collider)
      );
    }

    return MakeUnique<RigidBodyComponent>(
      gameObject,
      m_physicWorld,
      type,
      std::move(collider)
    );
  }
}