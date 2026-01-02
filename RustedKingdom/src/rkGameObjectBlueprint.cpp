#include "rkGameObjectBlueprint.h"
#include "rkGameObject.h"
#include "rkGameObjectBuilder.h"

namespace rk
{
  GameObjectBlueprint::GameObjectBlueprint()
  {
  }

  GameObjectBlueprint::~GameObjectBlueprint()
  {
  }

  void GameObjectBlueprint::apply(GameObject& gameObject) const
  {
    // Default implementation does nothing
  }

  GameObject* GameObjectBlueprint::instantiate(
    const String& name,
    GameObject& parent
  ) const
  {
    GameObjectBuilder builder;
    GameObject* gameObject = builder
      .createGameObject(name)
      .buildWithParent(parent);

    apply(*gameObject);

    return gameObject;
  }
}