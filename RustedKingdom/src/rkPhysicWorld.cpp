#include "rkPhysicWorld.h"
#include "rkRigidBody.h"
#include "rkCircleCollider.h"
#include "rkPhysicWorldListener.h"
#include "rkCollidersGroup.h"

namespace rk
{
  const String PhysicWorld::BaseColliderGroupName = "_Base";

  PhysicWorld::PhysicWorld() :
    m_rigidBodies(),
    m_listeners(),
    m_collidersGroups()
  {
    createCollidersGroup(PhysicWorld::BaseColliderGroupName);
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
    for (auto& pair : m_collidersGroups)
    {
      CollidersGroup* group = pair.second.get();
      if (group && group->removeCollider(collider))
        break;
    }
  }

  const Vector<UniquePtr<Collider>>& PhysicWorld::getColliders(
    const String& collidersGroupKey
  ) const
  {
    const CollidersGroup* colliderGroup = getCollidersGroup(collidersGroupKey);
    if (colliderGroup == nullptr)
    {
      throw InvalidArgumentException(
        String::Format(
          "PhysicWorld::getColliders: Colliders group '%s' not found.",
          collidersGroupKey
        )
      );
    }

    return colliderGroup->getColliders();
  }

  void PhysicWorld::addListener(PhysicWorldListener* listener)
  {
    auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
    if (it == m_listeners.end())
      m_listeners.push_back(listener);
  }

  void PhysicWorld::removeListener(PhysicWorldListener* listener)
  {
    auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
    if (it != m_listeners.end())
      m_listeners.erase(it);
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

  void PhysicWorld::createCollidersGroup(const String& key)
  {
    auto it = m_collidersGroups.find(key);
    if (it != m_collidersGroups.end())
    {
      throw InvalidArgumentException(
        String::Format(
          "PhysicWorld::createCollidersGroup: Colliders group '%s' already created.",
          key
        )
      );
    }

    m_collidersGroups[key] = MakeUnique<CollidersGroup>(key);
  }

  Collider* PhysicWorld::createCollider(
    GameObject& gameObject,
    colliderType::Type type
  )
  {
    return createCollider(
      gameObject,
      type,
      PhysicWorld::BaseColliderGroupName
    );
  }

  Collider* PhysicWorld::createCollider(
    GameObject& gameObject,
    colliderType::Type type,
    const String& colliderGroupKey
  )
  {
    if (type == colliderType::Circle)
    {
      UniquePtr<Collider> collider = MakeUnique<CircleCollider>(
        gameObject
      );

      Collider* rawPtr = collider.get();
      addColliderToGroup(colliderGroupKey, std::move(collider));
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

    for (auto& pair : m_collidersGroups)
    {
      CollidersGroup* group = pair.second.get();
      Vector<UniquePtr<Collider>>& colliders = group->getColliders();

      for (const auto& collider : colliders)
      {
        collider->syncGameObjectPositionToCollider();

        if (collider->isDirty())
        {
          collider->setDirtyFlag(false);
          notifyColliderChanged(collider.get());
        }
      }
    }
  }

  void PhysicWorld::clear()
  {
    m_rigidBodies.clear();
    m_collidersGroups.clear();
    m_listeners.clear();
  }

  void PhysicWorld::addColliderToGroup(
    const String& key,
    UniquePtr<Collider> collider
  )
  {
    CollidersGroup* group = getCollidersGroup(key);
    if (group == nullptr)
    {
      throw InvalidArgumentException(
        String::Format(
          "PhysicWorld::getColliders: Colliders group '%s' not found.",
          key
        )
      );
    }

    group->addCollider(std::move(collider));
  }

  CollidersGroup* PhysicWorld::getCollidersGroup(const String& key)
  {
    auto it = m_collidersGroups.find(key);
    if (it != m_collidersGroups.end())
      return it->second.get();
    return nullptr;
  }

  const CollidersGroup* PhysicWorld::getCollidersGroup(const String& key) const
  {
    auto it = m_collidersGroups.find(key);
    if (it != m_collidersGroups.end())
      return it->second.get();
    return nullptr;
  }

  void PhysicWorld::notifyColliderChanged(Collider* collider)
  {
    for (PhysicWorldListener* listener : m_listeners)
      listener->onColliderChanged(collider);
  }
}