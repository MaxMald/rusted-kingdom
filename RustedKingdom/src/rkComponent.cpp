#include "rkComponent.h"

namespace rk
{
  Component::Component(GameObject& gameObject) :
    m_gameObject(&gameObject)
  {
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