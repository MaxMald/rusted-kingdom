#include "rkBoxSelectorBlueprint.h"
#include "rkGameObject.h"
#include "rkGameObjectBuilder.h"
#include "rkColorUtilities.h"

#include "scripts/rkBoxSelectorScript.h"

namespace rk
{
  BoxSelectorBlueprint::BoxSelectorBlueprint(ComponentFactoryLocator& componentFactoryLocator) :
    GameObjectBlueprint(componentFactoryLocator)
  {
  }

  BoxSelectorBlueprint::~BoxSelectorBlueprint()
  {
  }

  void BoxSelectorBlueprint::apply(GameObject& gameObject) const
  {
    UniquePtr<BoxSelectorScript> boxSelectorScript =
      MakeUnique<BoxSelectorScript>(gameObject);

    boxSelectorScript->setBorderColor(colorUtilities::getColorFromHex("0054a0ff"));
    boxSelectorScript->setFillColor(colorUtilities::getColorFromHex("0085ff31"));
    boxSelectorScript->setBorderThickness(2.f);

    gameObject.addComponent(std::move(boxSelectorScript));
  }
}