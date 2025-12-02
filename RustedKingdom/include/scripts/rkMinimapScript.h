#pragma once

#include "rkScriptComponent.h"

namespace rk
{
  class MinimapScript : public ScriptComponent
  {
  public:
    MinimapScript(GameObject& gameObject);
    virtual ~MinimapScript();
  };
}