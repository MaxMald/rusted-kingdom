#pragma once

#include "rkBaseTiledClassApplier.h"

namespace rk
{
  class MinimapTiledClassApplier : public BaseTiledClassApplier
  {
  public:
    MinimapTiledClassApplier();
    virtual ~MinimapTiledClassApplier();

    virtual void apply(
      GameObject&,
      const tmr::Object*,
      const tmr::TiledMap*
    ) override;
  };
}