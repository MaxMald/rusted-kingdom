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
    void setCenter(const Vector2f& center) { m_center = center; }
    const Vector2f& getPosition() const { return m_position; }
    void setPosition(const Vector2f& position) { m_position = position; }
    colliderType::Type getType() const { return m_type; }
    GameObject& getGameObject() { return m_gameObject; }

    virtual bool checkCollision(const Collider& other) const = 0;
    virtual bool checkCollision(const Vector2f& point) const = 0;

  protected:
    Vector2f m_center;
    Vector2f m_position;
    colliderType::Type m_type;
    GameObject& m_gameObject;

    void syncGameObjectPositionToCollider();

    friend class PhysicWorld;
  };
}