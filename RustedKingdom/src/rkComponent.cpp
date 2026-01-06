#include "rkComponent.h"

namespace rk
{
  Component::Component(GameObject& gameObject) :
    m_gameObject(&gameObject)
  {
  }

  const GameObject& Component::getGameObject() const
  {
    return *m_gameObject;
  }

  GameObject& Component::getGameObject()
  {
    return *m_gameObject;
  }

  void Component::onCreate()
  {
  }

  void Component::onUpdate(float)
  {
  }

  void Component::onDraw(sf::RenderTarget&, sf::RenderStates) const
  {
  }

  void Component::onDelete()
  {
  }
}