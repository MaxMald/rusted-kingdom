#include "rkComponent.h"

namespace rk
{
  Component::Component(GameObject& gameObject, componentType::Type type) :
    m_gameObject(&gameObject),
    m_type(type)
  {
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