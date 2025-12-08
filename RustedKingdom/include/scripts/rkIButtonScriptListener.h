#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class GameObject;

  class IButtonScriptListener
  {
  public:
    virtual ~IButtonScriptListener() = default;
    virtual void onButtonClicked(GameObject& buttonGameObject) = 0;
  };
}