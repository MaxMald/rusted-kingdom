#pragma once

#include "rkGameObjectBlueprint.h"

namespace rk
{
  class BoxSelectorBlueprint : public GameObjectBlueprint
  {
  public:
    BoxSelectorBlueprint();
    virtual ~BoxSelectorBlueprint();

  protected:
    virtual GameObject* instantiate(
      const String& name,
      GameObject& parent
    ) const;
  };
}