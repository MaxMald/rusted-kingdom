#pragma once

#include "rkComponent.h"
#include "rkViewController.h"

namespace rk
{
  class ViewComponent : public Component
  {
  public:
    ViewComponent(GameObject&, SharedPtr<ViewController>);
    virtual ~ViewComponent();

    void move(const sf::Vector2f& offset);

  private:
    SharedPtr<ViewController> m_viewController;
  };
}