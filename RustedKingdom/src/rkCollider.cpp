#include "rkCollider.h"
#include "rkGameObject.h"

namespace rk
{
  Collider::Collider(GameObject& gameObject, colliderType::Type type) :
    m_gameObject(gameObject),
    m_type(type),
    m_center(0.0f, 0.0f),
    m_position(0.0f, 0.0f),
    m_isDirty(true),
    m_collidersGroupKey("")
  {
    syncGameObjectPositionToCollider();
  }

  Collider::~Collider()
  {
  }

  void Collider::syncGameObjectPositionToCollider()
  {
    Vector2f desiredPosition = m_gameObject.getWorldPosition();
    if (m_position != desiredPosition)
      setPosition(desiredPosition);
  }
}