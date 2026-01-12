#include "scripts/rkUnitsCommanderScript.h"

#include "rkGameObject.h"

#include "scripts/rkUnitController.h"
#include "scripts/rkUnitsSelectionController.h"

namespace rk
{
  UnitsCommanderScript::UnitsCommanderScript(GameObject& gameObject) :
    ScriptComponent(gameObject),
    m_unitsSelectionController(nullptr)
  {
  }

  UnitsCommanderScript::~UnitsCommanderScript()
  {
  }

  void UnitsCommanderScript::moveSelectedUnitsTo(const sf::Vector2f& position)
  {
    if (!m_unitsSelectionController)
      return;

    const Vector<GameObject*>& selectedUnits =
      m_unitsSelectionController->getCurrentlySelectedUnits();

    for (GameObject* unitObject : selectedUnits)
    {
      UnitController* unitController =
        unitObject->getComponent<UnitController>();

      if (unitController)
        unitController->goTo(position);
    }
  }

  void UnitsCommanderScript::onCreate()
  {
    m_unitsSelectionController =
      m_gameObject->getComponent<UnitsSelectionController>();
  }
}