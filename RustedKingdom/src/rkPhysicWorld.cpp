#include "rkPhysicWorld.h"
#include "rkRigidBody.h"
#include "rkCircleCollider.h"

namespace rk
{
  PhysicWorld::PhysicWorld() :
    m_rigidBodies()
  {
  }

  PhysicWorld::~PhysicWorld()
  {
    clear();
  }

  RigidBody* PhysicWorld::createRigidBody(
    rigidBodyType::Type type,
    GameObject& gameObject
  )
  {
    UniquePtr<RigidBody> rigidBody = MakeUnique<RigidBody>(
      type,
      gameObject
    );

    RigidBody* rawPtr = rigidBody.get();
    m_rigidBodies.push_back(std::move(rigidBody));
    return rawPtr;
  }

  void PhysicWorld::destroyCollider(Collider* collider)
  {
    auto it = std::find_if(
      m_colliders.begin(),
      m_colliders.end(),
      [collider](const UniquePtr<Collider>& ptr)
      {
        return ptr.get() == collider;
      }
    );

    if (it != m_colliders.end())
      m_colliders.erase(it);
  }

  void PhysicWorld::destroyRigidBody(RigidBody* rigidBody)
  {
    auto it = std::find_if(
      m_rigidBodies.begin(),
      m_rigidBodies.end(),
      [rigidBody](const UniquePtr<RigidBody>& ptr)
      {
        return ptr.get() == rigidBody;
      }
    );

    if (it != m_rigidBodies.end())
      m_rigidBodies.erase(it);
  }

  Collider* PhysicWorld::createCollider(
    GameObject& gameObject,
    colliderType::Type type
  )
  {
    if (type == colliderType::Circle)
    {
      UniquePtr<Collider> collider = MakeUnique<CircleCollider>(
        gameObject
      );
      Collider* rawPtr = collider.get();
      m_colliders.push_back(std::move(collider));
      return rawPtr;
    }

    throw RuntimeErrorException(
      String::Format(
        "PhysicWorld::createCollider: Unsupported collider type %d.",
        static_cast<int>(type)
      )
    );
  }

  void PhysicWorld::update(float deltaTime)
  {
    for (const auto& rigidBody : m_rigidBodies)
      rigidBody->syncGameObjectPositionToRigidBody();

    for (const auto& rigidBody : m_rigidBodies)
      rigidBody->update(deltaTime);

    for (const auto& rigidBody : m_rigidBodies)
      rigidBody->syncRigidBodyPositionToGameObject();

    for (const auto& collider : m_colliders)
      collider->syncGameObjectPositionToCollider();
  }

  void PhysicWorld::clear()
  {
    m_rigidBodies.clear();
  }
}