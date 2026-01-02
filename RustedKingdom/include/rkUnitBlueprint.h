#pragma once

#include "rkGameObjectBlueprint.h"

namespace rk
{
  class UnitBlueprint : public GameObjectBlueprint
  {
  public:
    UnitBlueprint(ComponentFactoryLocator&);
    virtual ~UnitBlueprint();

    virtual void apply(GameObject& gameObject) const override;
  };
}