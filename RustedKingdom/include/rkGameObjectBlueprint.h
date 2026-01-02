#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class GameObject;

  class GameObjectBlueprint : public NonCopyable
  {
  public:
    GameObjectBlueprint();
    virtual ~GameObjectBlueprint();

    virtual void apply(GameObject& gameObject) const;
    GameObject* instantiate(const String& name, GameObject& parent) const;
  };
}