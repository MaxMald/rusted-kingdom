#include "rkArmyManager.h"
#include "rkArmy.h"
#include "rkFactionManager.h"
#include "rkServiceLocator.h"

namespace rk
{
  SharedPtr<Army> ArmyManager::getArmy(UInt32 armyId)
  {
    auto it = m_armies.find(armyId);
    if (it != m_armies.end())
      return it->second;

    return SharedPtr<Army>();
  }

  SharedPtr<Army> ArmyManager::getArmy(const String& name)
  {
    for (const auto& [id, army] : m_armies)
    {
      if (army->getName() == name)
        return army;
    }

    return SharedPtr<Army>();
  }

  SharedPtr<Army> ArmyManager::getUserArmy()
  {
    for (const auto& [id, army] : m_armies)
    {
      if (army->getControlType() == armyControlType::User)
        return army;
    }

    return SharedPtr<Army>();
  }

  void ArmyManager::setArmiesAsAllies(UInt32 armyIdA, UInt32 armyIdB)
  {
    SharedPtr<Army> armyA = getArmy(armyIdA);
    SharedPtr<Army> armyB = getArmy(armyIdB);

    if (!armyA || !armyB)
    {
      // TODO log error
      return;
    }

    if (armyA->isAlliedWith(*armyB))
      return;

    armyA->removeHostileArmy(*armyB);
    armyB->removeHostileArmy(*armyA);
    armyA->addAlliedArmy(*armyB);
    armyB->addAlliedArmy(*armyA);
  }

  void ArmyManager::setArmiesAsHostiles(UInt32 armyIdA, UInt32 armyIdB)
  {
    SharedPtr<Army> armyA = getArmy(armyIdA);
    SharedPtr<Army> armyB = getArmy(armyIdB);

    if (!armyA || !armyB)
    {
      // TODO log error
      return;
    }

    if (armyA->isHostileTo(*armyB))
      return;

    armyA->removeAlliedArmy(*armyB);
    armyB->removeAlliedArmy(*armyA);
    armyA->addHostileArmy(*armyB);
    armyB->addHostileArmy(*armyA);
  }

  const UnorderedMap<UInt32, SharedPtr<Army>>& ArmyManager::getAllArmies() const
  {
    return m_armies;
  }

  SharedPtr<Army> ArmyManager::createArmy(
    const String& name,
    factionType::Type factionType,
    armyControlType::Type controlType
  )
  {
    SharedPtr<FactionManager> factionManager =
      ServiceLocator::Instance().getService<FactionManager>();

    SharedPtr<Army> newArmy = SharedPtr<Army>(
      new Army(
        static_cast<UInt32>(m_armies.size() + 1),
        name,
        factionManager->getFaction(factionType),
        controlType
      )
    );

    m_armies[newArmy->getId()] = newArmy;
    return newArmy;
  }

  void ArmyManager::clear()
  {
    m_armies.clear();
  }

  void ArmyManager::init(ServiceLocator&)
  {
  }

  void ArmyManager::destroy()
  {
    m_armies.clear();
  }
}