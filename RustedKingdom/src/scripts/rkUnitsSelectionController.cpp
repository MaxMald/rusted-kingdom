#include "scripts/rkUnitsSelectionController.h"

#include "rkGameObject.h"
#include "rkArmy.h"

#include "scripts/rkUnitController.h"
#include "scripts/rkBoxSelectorScript.h"

namespace rk
{
  UnitsSelectionController::UnitsSelectionController(GameObject& gameObject) :
    ScriptComponent(gameObject)
  {
  }

  UnitsSelectionController::~UnitsSelectionController()
  {
  }

  void UnitsSelectionController::onBoxSelectionStarted(
    const Vector2f& boxP1,
    const Vector2f& boxP2
  )
  {
    if (!m_army)
      return;
  }

  void UnitsSelectionController::onBoxSelectionUpdated(
    const Vector2f& boxP1,
    const Vector2f& boxP2
  )
  {
    if (!m_army)
      return;

    selectsUnitsOnArea(boxP1, boxP2);
  }

  void UnitsSelectionController::onBoxSelectionEnded(
    const Vector2f& boxP1,
    const Vector2f& boxP2
  )
  {
    if (!m_army)
      return;

    selectsUnitsOnArea(boxP1, boxP2);
  }

  void UnitsSelectionController::setArmy(SharedPtr<Army> army)
  {
    m_army = army;
  }

  const Vector<GameObject*>& UnitsSelectionController::getCurrentlySelectedUnits() const
  {
    return m_currentlySelectedUnits;
  }

  void UnitsSelectionController::onCreate()
  {
    registerEvents();
  }

  void UnitsSelectionController::registerEvents()
  {
    BoxSelectorScript* boxSelectoScript =
      m_gameObject->getComponent<BoxSelectorScript>();

    boxSelectoScript->registerListener(this);
  }

  void UnitsSelectionController::selectsUnitsOnArea(
    const Vector2f& boxP1,
    const Vector2f& boxP2
  )
  {
    m_currentlySelectedUnits.clear();

    if (!m_army)
      return;

    const Vector<UnitController*>& armyUnits = m_army->getUnits();
    for (UnitController* unitController : armyUnits)
    {
      GameObject& unitGo = unitController->getGameObject();

      Vector2f unitPosition = unitGo.getWorldPosition();
      if (
        unitPosition.x >= std::min(boxP1.x, boxP2.x) &&
        unitPosition.x <= std::max(boxP1.x, boxP2.x) &&
        unitPosition.y >= std::min(boxP1.y, boxP2.y) &&
        unitPosition.y <= std::max(boxP1.y, boxP2.y)
      )
      {
        m_currentlySelectedUnits.push_back(&unitGo);
      }
    }
  }
}