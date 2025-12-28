#include "scripts/rkUnitController.h"

namespace rk
{
  UnitController::UnitController(
    GameObject& gameObject,
    const UnitDescription& unitDescription,
    SharedPtr<Army> army
  ) :
    ScriptComponent(gameObject),
    m_unitDescription(unitDescription),
    m_army(army)
  {
    m_currentHealth = m_unitDescription.getHealth();
  }

  UnitController::~UnitController()
  {
  }

  SharedPtr<Army> UnitController::getArmy()
  {
    return m_army;
  }

  void UnitController::setArmy(SharedPtr<Army> army)
  {
    m_army = army;
  }

  const UnitDescription& UnitController::getUnitDescription() const
  {
    return m_unitDescription;
  }

  UInt16 UnitController::getCurrentHealth() const
  {
    return m_currentHealth;
  }

  void UnitController::addDamage(UInt16 damage)
  {
    m_currentHealth -= damage;
  }

  void UnitController::addHealth(UInt16 health)
  {
    m_currentHealth += health;
    if (m_currentHealth > m_unitDescription.getHealth())
      m_currentHealth = m_unitDescription.getHealth();
  }

  void UnitController::onCreate()
  {
  }

  void UnitController::onDelete()
  {
  }
}