#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"
#include "rkColliderType.h"
#include "rkNonCopyable.h"

using sf::Vector2f;

namespace rk
{
  class GameObject;

  class Collider : public NonCopyable
  {
  public:
    Collider(GameObject& gameObject, colliderType::Type type);
    virtual ~Collider();

    const Vector2f& getCenter() const { return m_center; }
    void setCenter(const Vector2f& center) { m_center = center; m_isDirty = true; }
    const Vector2f& getPosition() const { return m_position; }
    void setPosition(const Vector2f& position) { m_position = position; m_isDirty = true; }
    colliderType::Type getType() const { return m_type; }
    GameObject& getGameObject() { return m_gameObject; }
    bool isDirty() const { return m_isDirty; }
    const String& getCollidersGroupKey() const { return m_collidersGroupKey; }

    virtual bool checkCollision(const Collider& other) const = 0;
    virtual bool checkCollision(const Vector2f& point) const = 0;

  protected:
    String m_collidersGroupKey;
    Vector2f m_center;
    Vector2f m_position;
    bool m_isDirty;
    colliderType::Type m_type;
    GameObject& m_gameObject;

    void setCollidersGroupKey(const String& key) { m_collidersGroupKey = key; }
    void setDirtyFlag(bool isDirty) { m_isDirty = isDirty; }
    void syncGameObjectPositionToCollider();

    friend class PhysicWorld;
    friend class CollidersGroup;
  };
}