#include "rkLayerGameObjectBlueprint.h"
#include "rkLayerGameObject.h"

namespace rk
{
  GameObject* LayerGameObjectBlueprint::instantiate(
    const String& name,
    GameObject& parent
  ) const
  {
    LayerGameObject* layerGameObject = new LayerGameObject(name.c_str());
    parent.addChild(UniquePtr<GameObject>(layerGameObject));
    return layerGameObject;
  }
}