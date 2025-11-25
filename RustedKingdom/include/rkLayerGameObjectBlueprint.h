#pragma once

#include "rkGameObjectBlueprint.h"

namespace rk
{
  class LayerGameObjectBlueprint : public GameObjectBlueprint
  {
  public:
    LayerGameObjectBlueprint() = default;
    ~LayerGameObjectBlueprint() override = default;

  protected:
    virtual GameObject* instantiate(
      const String& name,
      GameObject& parent
    ) const override;
  };
}