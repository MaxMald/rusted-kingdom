#include "rkPhysicWorld.h"
#include "rkRigidBody.h"

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

  RigidBody* PhysicWorld::createRigidBody(rigidBodyType::Type type)
  {
    UniquePtr<RigidBody> rigidBody = MakeUnique<RigidBody>(type);
    RigidBody* rawPtr = rigidBody.get();
    m_rigidBodies.push_back(std::move(rigidBody));
    return rawPtr;
  }

  void PhysicWorld::destroyRigidBody(RigidBody* rigidBody)
  {
    auto it = std::find(
      m_rigidBodies.begin(),
      m_rigidBodies.end(),
      rigidBody
    );

    if (it != m_rigidBodies.end())
      m_rigidBodies.erase(it);
  }

  void PhysicWorld::update(float deltaTime)
  {
    for (const auto& rigidBody : m_rigidBodies)
      rigidBody->update(deltaTime);
  }

  void PhysicWorld::clear()
  {
    m_rigidBodies.clear();
  }
}