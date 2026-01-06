#include "rkArmy.h"
#include "scripts/rkUnitController.h"

namespace rk
{
  Army::Army(
    UInt32 id,
    const String& name,
    const Faction& faction,
    armyControlType::Type controlType
  )
    : m_id(id)
    , m_name(name)
    , m_faction(faction)
    , m_controlType(controlType)
  {
  }

  Army::~Army()
  {
  }

  const String& Army::getName() const
  {
    return m_name;
  }

  factionType::Type Army::getFactionType() const
  {
    return m_faction.getType();
  }

  armyControlType::Type Army::getControlType() const
  {
    return m_controlType;
  }

  UInt32 Army::getId() const
  {
    return m_id;
  }

  bool Army::isAlliedWith(const Army& otherArmy) const
  {
    return std::find(
      m_alliedArmyIds.begin(),
      m_alliedArmyIds.end(),
      otherArmy.getId()
    ) != m_alliedArmyIds.end();
  }

  bool Army::isHostileTo(const Army& otherArmy) const
  {
    return std::find(
      m_hostileArmyIds.begin(),
      m_hostileArmyIds.end(),
      otherArmy.getId()
    ) != m_hostileArmyIds.end();
  }

  void Army::addUnit(UnitController* unitController)
  {
    m_units.push_back(unitController);
  }

  void Army::removeUnit(UnitController* unitController)
  {
    auto it = std::remove(m_units.begin(), m_units.end(), unitController);
    if (it != m_units.end())
    {
      m_units.erase(it, m_units.end());
    }
  }

  const Vector<UnitController*>& Army::getUnits() const
  {
    return m_units;
  }

  void Army::clearUnits()
  {
    for (UnitController* unitController : m_units)
      unitController->setArmy(nullptr);
    m_units.clear();
  }

  void Army::addAlliedArmy(const Army& otherArmy)
  {
    if (this->getId() == otherArmy.getId())
      return;

    m_alliedArmyIds.push_back(otherArmy.getId());
  }

  void Army::addHostileArmy(const Army& otherArmy)
  {
    if (this->getId() == otherArmy.getId())
      return;

    m_hostileArmyIds.push_back(otherArmy.getId());
  }

  void Army::removeAlliedArmy(const Army& otherArmy)
  {
    if (this->getId() == otherArmy.getId())
      return;

    auto it = std::remove(
      m_alliedArmyIds.begin(),
      m_alliedArmyIds.end(),
      otherArmy.getId()
    );

    if (it != m_alliedArmyIds.end())
    {
      m_alliedArmyIds.erase(it, m_alliedArmyIds.end());
    }
  }

  void Army::removeHostileArmy(const Army& otherArmy)
  {
    if (this->getId() == otherArmy.getId())
      return;

    auto it = std::remove(
      m_hostileArmyIds.begin(),
      m_hostileArmyIds.end(),
      otherArmy.getId()
    );

    if (it != m_hostileArmyIds.end())
    {
      m_hostileArmyIds.erase(it, m_hostileArmyIds.end());
    }
  }
}