#pragma once

#include "rkGameObjectBlueprint.h"

namespace rk
{
  class CorpoBasicSoldierBlueprint : public GameObjectBlueprint
  {
  public:
    CorpoBasicSoldierBlueprint();
    virtual ~CorpoBasicSoldierBlueprint();

    virtual void apply(GameObject& gameObject) const override;
  };
}