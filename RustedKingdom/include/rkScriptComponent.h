#pragma once

#include "rkComponent.h"

namespace rk
{
  class ScriptComponent : public Component
  {
  public:
    ScriptComponent(GameObject& gameObject);
    virtual ~ScriptComponent();
  };
}