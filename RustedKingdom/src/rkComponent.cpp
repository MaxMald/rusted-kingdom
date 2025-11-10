#include "rkComponent.h"

namespace rk
{
  Component::Component(GameObject& gameObject, componentType::Type type) :
    m_gameObject(&gameObject),
    m_type(type)
  {
  }

  Component::Component(Component&& other) noexcept :
    m_gameObject(other.m_gameObject),
    m_type(other.m_type)
  {
    other.m_gameObject = nullptr;
  }

  Component& Component::operator=(Component&& other) noexcept
  {
    if (this != &other)
    {
      m_gameObject = other.m_gameObject;
      m_type = other.m_type;
      other.m_gameObject = nullptr;
    }
    return *this;
  }

  void Component::onUpdate(float deltaTime)
  {
    (void)deltaTime;
  }

  void Component::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    (void)target;
    (void)states;
  }


  void Component::onDelete()
  {
  }
}