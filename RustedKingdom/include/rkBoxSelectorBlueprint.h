#pragma once

#include "rkGameObjectBlueprint.h"

namespace rk
{
  class BoxSelectorBlueprint : public GameObjectBlueprint
  {
  public:
    BoxSelectorBlueprint();
    virtual ~BoxSelectorBlueprint();

    virtual void apply(GameObject& gameObject) const;
  };
}