#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkRigidBodyType.h"
#include "rkColliderType.h"

namespace rk
{
  class RigidBody;
  class GameObject;
  class Collider;

  /**
  * @brief Manages the simulation and lifetime of all RigidBody instances in the
  * physics world.
  *
  * PhysicWorld is responsible for creating, updating, and destroying RigidBody
  * objects. It owns all RigidBody memory and provides an update loop for physics
  * simulation. Use createRigidBody to instantiate new bodies, destroyRigidBody
  * for cleanup, and update to advance the simulation.
  */
  class PhysicWorld : public NonCopyable
  {
  public:
    PhysicWorld();
    ~PhysicWorld();

    RigidBody* createRigidBody(rigidBodyType::Type, GameObject&);
    void destroyRigidBody(RigidBody* rigidBody);
    Collider* createCollider(GameObject&, colliderType::Type type);
    void destroyCollider(Collider* collider);
    void update(float deltaTime);
    void clear();

  private:
    Vector<UniquePtr<RigidBody>> m_rigidBodies;
    Vector<UniquePtr<Collider>> m_colliders;
  };
}