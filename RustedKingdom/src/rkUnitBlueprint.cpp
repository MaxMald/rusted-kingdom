#include "rkUnitBlueprint.h"

namespace rk
{
  UnitBlueprint::UnitBlueprint(ComponentFactoryLocator& componentFactoryLocator) : 
    GameObjectBlueprint(componentFactoryLocator)
  {
  }

  UnitBlueprint::~UnitBlueprint()
  {
  }

  void UnitBlueprint::apply(GameObject& gameObject) const
  {
  }
}