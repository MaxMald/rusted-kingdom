#include "rkViewComponentFactory.h"
#include "rkViewsManager.h"
#include "rkViewController.h"

namespace rk
{
  ViewComponentFactory::ViewComponentFactory(
    SharedPtr<ViewsManager> viewsManager
  ) :
    m_viewsManager(viewsManager)
  {
  }

  ViewComponentFactory::~ViewComponentFactory()
  {
  }

  UniquePtr<ViewComponent> ViewComponentFactory::create(
    GameObject& gameObject,
    const String& viewName
  )
  {
    SharedPtr<ViewController> viewController = MakeShared<ViewController>(
      viewName,
      m_viewsManager->getDefaultSfmlView()
    );
    m_viewsManager->addView(viewController);

    return MakeUnique<ViewComponent>(gameObject, viewController);
  }
}