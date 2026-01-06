#include "rkCorpoBasicSoldierBlueprint.h"

#include <TMR/tmrObject.h>

#include "rkServiceLocator.h"
#include "rkGameObject.h"
#include "rkCorpSoldierClassApplier.h"
#include "rkTiledPropertiesHandler.h"
#include "rkArmyManager.h"
#include "rkArmy.h"

#include "scripts/rkUnitController.h"

namespace rk
{
  CorpoSoldierClassApplier::CorpoSoldierClassApplier(
    SharedPtr<GameObjectBlueprint> blueprint
  ) : BlueprintClassApplier(blueprint)
  {
  }

  CorpoSoldierClassApplier::~CorpoSoldierClassApplier()
  {
  }

  void CorpoSoldierClassApplier::initProperties(
    GameObject& gameObject,
    const tmr::Object* tmrObject
  )
  {
    TiledPropertiesHandler propertiesHandler(tmrObject->getProperties());

    String armyName;
    propertiesHandler.tryGetString("armyName", armyName);

    UnitController* unitController = gameObject
      .getComponent<UnitController>();

    SharedPtr<ArmyManager> armyManager 
      = ServiceLocator::Instance().getService<ArmyManager>();

    unitController->setArmy(armyManager->getArmy(armyName));
  }
}