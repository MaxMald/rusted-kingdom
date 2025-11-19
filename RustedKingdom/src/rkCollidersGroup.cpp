#include "rkCollidersGroup.h"
#include "rkCollider.h"

namespace rk
{
  CollidersGroup::CollidersGroup(const String& key) :
    m_key(key)
  {
  }

  CollidersGroup::~CollidersGroup()
  {
    m_colliders.clear();
  }

  const Vector<UniquePtr<Collider>>& CollidersGroup::getColliders() const {
    return m_colliders;
  }

  Vector<UniquePtr<Collider>>& CollidersGroup::getColliders()
  {
    return m_colliders;
  }

  void CollidersGroup::addCollider(UniquePtr<Collider> collider)
  {
    collider->setCollidersGroupKey(m_key);
    m_colliders.push_back(std::move(collider));
  }

  bool CollidersGroup::removeCollider(Collider* collider)
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
    {
      m_colliders.erase(it);
      return true;
    }
    
    return false;
  }
}