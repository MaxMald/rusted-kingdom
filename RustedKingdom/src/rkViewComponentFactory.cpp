#include "rkViewComponentFactory.h"
#include "rkServiceLocator.h"
#include "rkViewsManager.h"
#include "rkViewController.h"

namespace rk
{
  namespace viewComponentFactory
  {
    UniquePtr<ViewComponent> create(
      GameObject& gameObject,
      const String& viewName
    )
    {
      const SharedPtr<ViewsManager> viewsManager =
        ServiceLocator::Instance().getService<ViewsManager>();

      SharedPtr<ViewController> viewController = MakeShared<ViewController>(
        viewName,
        viewsManager->getDefaultSfmlView()
      );

      viewsManager->addView(viewController);

      return MakeUnique<ViewComponent>(gameObject, viewController);
    }
  }
}