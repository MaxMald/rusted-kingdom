#include "rkBoxSelectorBlueprint.h"
#include "rkGameObject.h"
#include "rkGameObjectBuilder.h"
#include "rkColorUtilities.h"

#include "scripts/rkBoxSelectorScript.h"

namespace rk
{
  BoxSelectorBlueprint::BoxSelectorBlueprint()
  {
  }

  BoxSelectorBlueprint::~BoxSelectorBlueprint()
  {
  }

  GameObject* BoxSelectorBlueprint::instantiate(
    const String& name,
    GameObject& parent
  ) const
  {
    GameObjectBuilder builder;
    GameObject* boxSelector = builder
      .createGameObject(name)
      .buildWithParent(parent);

    UniquePtr<BoxSelectorScript> boxSelectorScript =
      MakeUnique<BoxSelectorScript>(*boxSelector);

    boxSelectorScript->setBorderColor(colorUtilities::getColorFromHex("0054a0ff"));
    boxSelectorScript->setFillColor(colorUtilities::getColorFromHex("0085ff31"));
    boxSelectorScript->setBorderThickness(2.f);

    boxSelector->addComponent(std::move(boxSelectorScript));

    return boxSelector;
  }
}