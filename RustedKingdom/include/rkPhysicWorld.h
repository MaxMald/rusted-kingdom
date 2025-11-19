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
  class PhysicWorldListener;
  class CollidersGroup;

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
    static const String BaseColliderGroupName;

    PhysicWorld();
    ~PhysicWorld();

    RigidBody* createRigidBody(rigidBodyType::Type, GameObject&);
    void destroyRigidBody(RigidBody* rigidBody);
    void createCollidersGroup(const String& key);
    Collider* createCollider(GameObject&, colliderType::Type type);
    Collider* createCollider(GameObject&, colliderType::Type type, const String& colliderGroupKey);
    void destroyCollider(Collider* collider);
    const Vector<UniquePtr<Collider>>& getColliders(const String& collidersGroupKey) const;

    void addListener(PhysicWorldListener* listener);
    void removeListener(PhysicWorldListener* listener);

    void update(float deltaTime);
    void clear();

  private:
    Vector<UniquePtr<RigidBody>> m_rigidBodies;
    UnorderedMap<String, UniquePtr<CollidersGroup>> m_collidersGroups;
    Vector<PhysicWorldListener*> m_listeners;

    void addColliderToGroup(const String& key, UniquePtr<Collider> collider);
    CollidersGroup* getCollidersGroup(const String& key);
    const CollidersGroup* getCollidersGroup(const String& key) const;
    void notifyColliderChanged(Collider* collider);
  };
}