#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class Collider;

  class CollidersGroup : public NonCopyable
  {
  public:
    CollidersGroup(const String& key);
    ~CollidersGroup();

    const Vector<UniquePtr<Collider>>& getColliders() const;
    Vector<UniquePtr<Collider>>& getColliders();
    const String& getKey() const { return m_key; }

    void addCollider(UniquePtr<Collider> collider);
    bool removeCollider(Collider* collider);

  private:
    String m_key;
    Vector<UniquePtr<Collider>> m_colliders;
  };
}