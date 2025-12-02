#include "rkMinimapBlueprint.h"

#include <TMR/tmrObject.h>

#include "rkGameObject.h"
#include "rkGameObjectBuilder.h"
#include "scripts/rkMinimapScript.h"

namespace rk
{
  MinimapBlueprint::MinimapBlueprint() :
    TiledGameObjectBlueprint()
  {
  }

  MinimapBlueprint::~MinimapBlueprint()
  {
  }

  GameObject* MinimapBlueprint::instantiate(
    const String& name,
    GameObject& parent
  ) const
  {
    if (!m_tmrObject)
    {
      throw RuntimeErrorException(
        String::Format(
          "MinimapBlueprint::instantiate: Tiled object not set for MinimapBlueprint '%s'.",
          name.c_str()
        )
      );
    }

    GameObjectBuilder builder;
    GameObject* minimap = builder
      .createGameObject(name)
      .buildWithParent(parent);

    minimap->addComponent(
      MakeUnique<MinimapScript>(*minimap)
    );

    return minimap;
  }
}