#pragma once

#include "rkGameObjectBlueprint.h"

namespace rk
{
  class BoxSelectorBlueprint : public GameObjectBlueprint
  {
  public:
    BoxSelectorBlueprint(ComponentFactoryLocator&);
    virtual ~BoxSelectorBlueprint();

    virtual void apply(GameObject& gameObject) const;
  };
}