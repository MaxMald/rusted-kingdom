#pragma once

#include "rkGameObjectBlueprint.h"

namespace rk
{
  class UnitBlueprint : public GameObjectBlueprint
  {
  public:
    UnitBlueprint();
    virtual ~UnitBlueprint();

    virtual void apply(GameObject& gameObject) const override;

  private:
  };
}