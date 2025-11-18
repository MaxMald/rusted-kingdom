#include "rkCollider.h"
#include "rkGameObject.h"

namespace rk
{
  Collider::Collider(GameObject& gameObject, colliderType::Type type) :
    m_gameObject(gameObject),
    m_type(type),
    m_center(0.0f, 0.0f),
    m_position(0.0f, 0.0f)
  {
  }

  Collider::~Collider()
  {
  }

  void Collider::syncGameObjectPositionToCollider()
  {
    m_position = m_gameObject.getWorldPosition();
  }
}