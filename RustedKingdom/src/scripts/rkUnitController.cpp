#include "scripts/rkUnitController.h"

#include "rkGameObject.h"
#include "rkArmy.h"
#include "rkPathfinderComponent.h"

#include "scripts/rkAgentPathMovement.h"

namespace rk
{
  UnitController::UnitController(
    GameObject& gameObject,
    const UnitDescription& unitDescription
  ) :
    ScriptComponent(gameObject),
    m_unitDescription(unitDescription),
    m_pathfinderComponent(nullptr),
    m_agentPathMovement(nullptr)
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
    if (m_army == army)
      return;

    if (m_army)
      m_army->removeUnit(this);

    if (army)
      army->addUnit(this);

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

  void UnitController::goTo(const Vector2f& position)
  {
    if (!m_agentPathMovement || !m_pathfinderComponent)
      return;

    Vector<Vector2f> path = m_pathfinderComponent->findPath(
      m_gameObject->getPosition(),
      position
    );

    if (path.empty())
      return;

    m_agentPathMovement->start(path);
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
    m_pathfinderComponent = m_gameObject->getComponent<PathfinderComponent>();
    m_agentPathMovement = m_gameObject->getComponent<AgentPathMovement>();
  }

  void UnitController::onDelete()
  {
    if (m_army)
      m_army->removeUnit(this);

    m_army = nullptr;
  }
}