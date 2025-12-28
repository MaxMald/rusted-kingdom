#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkFaction.h"
#include "rkArmyControlType.h"

namespace rk
{
  class ArmyManager;
  class UnitController;

  class Army : public NonCopyable
  {
  public:
    Army(
      UInt32 id,
      const String& name,
      const Faction& faction,
      armyControlType::Type controlType
    );
    ~Army();

    const String& getName() const;
    factionType::Type getFactionType() const;
    armyControlType::Type getControlType() const;
    UInt32 getId() const;

    bool isAlliedWith(const Army& otherArmy) const;
    bool isHostileTo(const Army& otherArmy) const;

    void addUnit(UnitController* unitController);
    void removeUnit(UnitController* unitController);
    const Vector<UnitController*>& getUnits() const;
    void clearUnits();

  protected:
    void addAlliedArmy(const Army& otherArmy);
    void addHostileArmy(const Army& otherArmy);
    void removeAlliedArmy(const Army& otherArmy);
    void removeHostileArmy(const Army& otherArmy);

  private:
    UInt32 m_id;
    String m_name;
    Faction m_faction;
    armyControlType::Type m_controlType;
    Vector<UInt32> m_alliedArmyIds;
    Vector<UInt32> m_hostileArmyIds;
    Vector<UnitController*> m_units;

    friend class ArmyManager;
  };
}