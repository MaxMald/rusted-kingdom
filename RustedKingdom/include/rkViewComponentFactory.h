#pragma once

#include "rkViewComponent.h"

namespace rk
{
  class ViewsManager;

  namespace viewComponentFactory
  {
    UniquePtr<ViewComponent> create(
      GameObject& gameObject,
      const String& viewName
    );
  }
}