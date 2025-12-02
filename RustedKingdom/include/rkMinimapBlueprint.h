#pragma once

#include "rkTiledGameObjectBlueprint.h"

namespace rk
{
  class MinimapBlueprint : public TiledGameObjectBlueprint
  {
  public:
    MinimapBlueprint();
    virtual ~MinimapBlueprint();

  protected:

    virtual GameObject* instantiate(
      const String& name,
      GameObject& parent
    ) const override;
  };
}