#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkViewComponent.h"

namespace rk
{
  class ViewsManager;

  class ViewComponentFactory : public NonCopyable
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