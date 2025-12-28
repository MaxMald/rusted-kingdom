#include "scripts/rkUnitController.h"

namespace rk
{
  UnitController::UnitController(GameObject& gameObject, const String& armyName) :
    ScriptComponent(gameObject)
  {

  }

  UnitController::~UnitController()
  {
  }

  SharedPtr<Army> UnitController::getArmy()
  {
    return SharedPtr<Army>();
  }

  void UnitController::setArmy(SharedPtr<Army> army)
  {
  }

  void UnitController::onCreate()
  {
  }

  void UnitController::onDelete()
  {
  }
}