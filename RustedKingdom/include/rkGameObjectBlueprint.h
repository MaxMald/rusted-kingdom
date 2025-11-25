#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class GameObject;

  class GameObjectBlueprint : public NonCopyable
  {
  public:
    GameObjectBlueprint() : NonCopyable() {}
    virtual ~GameObjectBlueprint() {}

  protected:
    virtual GameObject* instantiate(
      const String& name,
      GameObject& parent
    ) const = 0;

    friend class SceneGraph;
  };
}