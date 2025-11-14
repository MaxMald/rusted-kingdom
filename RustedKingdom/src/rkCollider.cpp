#include "rkCollider.h"

namespace rk
{
  Collider::Collider()
    : m_type(colliderType::Undefined)
  {
  }

  Collider::Collider(colliderType::Type type)
    : m_type(type)
  {
  }

  Collider::Collider(const Collider& other)
    : m_type(other.m_type)
  {
  }

  Collider::Collider(Collider&& other) noexcept
    : m_type(other.m_type)
  {
    other.m_type = colliderType::Undefined;
  }

  Collider::~Collider()
  {
  }

  Collider& Collider::operator=(const Collider& other)
  {
    if (this != &other)
      m_type = other.m_type;
    return *this;
  }

  Collider& Collider::operator=(Collider&& other) noexcept
  {
    if (this != &other)
    {
      m_type = other.m_type;
      other.m_type = colliderType::Undefined;
    }
    return *this;
  }
}