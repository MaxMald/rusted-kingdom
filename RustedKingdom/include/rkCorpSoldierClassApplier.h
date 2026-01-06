#pragma once

#include "rkBlueprintClassApplier.h"

namespace rk
{
  class CorpoSoldierClassApplier : public BlueprintClassApplier
  {
  public:
    CorpoSoldierClassApplier(SharedPtr<GameObjectBlueprint>);
    virtual ~CorpoSoldierClassApplier();

  protected:
    virtual void initProperties(
      GameObject&,
      const tmr::Object*
    ) override;
  };
}