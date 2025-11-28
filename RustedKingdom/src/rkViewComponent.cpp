#include "rkViewComponent.h"

namespace rk
{
  ViewComponent::ViewComponent(
    GameObject& gameObject,
    SharedPtr<ViewController> viewController
  ) :
    Component(gameObject, componentType::View),
    m_viewController(viewController)
  {
  }

  ViewComponent::~ViewComponent()
  {
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