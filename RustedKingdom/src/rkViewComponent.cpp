#include "rkViewComponent.h"

namespace rk
{
  ViewComponent::ViewComponent(
    GameObject& gameObject,
    SharedPtr<ViewController> viewController
  ) :
    Component(gameObject),
    m_viewController(viewController)
  {
  }

  ViewComponent::~ViewComponent()
  {
  }

  const String& ViewComponent::getViewName() const
  {
    if (m_viewController)
      return m_viewController->getName();
    
    throw RuntimeErrorException(
      "ViewComponent has no associated ViewController"
    );
  }

  void ViewComponent::move(const sf::Vector2f& offset)
  {
    if (m_viewController)
    {
      View view = m_viewController->getView();
      view.move(offset);
      m_viewController->setView(view);
    }
  }
}