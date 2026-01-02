#pragma once

#include "rkIComponentFactory.h"
#include "rkViewComponent.h"

namespace rk
{
  class ViewsManager;

  class ViewComponentFactory : public IComponentFactory
  {
  public:
    ViewComponentFactory(SharedPtr<ViewsManager> viewsManager);
    ~ViewComponentFactory();

    UniquePtr<ViewComponent> create(
      GameObject& gameObject,
      const String& viewName
    );

  private:
    SharedPtr<ViewsManager> m_viewsManager;
  };
}