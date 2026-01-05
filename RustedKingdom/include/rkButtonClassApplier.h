#pragma once

#include "rkBaseTiledClassApplier.h"

namespace rk
{
  class ButtonClassApplier : public BaseTiledClassApplier
  {
  public:
    ButtonClassApplier();
    virtual ~ButtonClassApplier();

    virtual void apply(
      GameObject& gameObject,
      const tmr::Object* object,
      const tmr::TiledMap* tiledMap
    ) override;
  };
}